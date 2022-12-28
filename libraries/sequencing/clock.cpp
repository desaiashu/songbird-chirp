// #acts as master clock
// #takes in midi clock if it's sensing one, otherwise sets BPM internally
// #registers instruments to master clock

#include "clock.h"
#if ARDUINO
#include <console.h>
#include <midi_io.h>
#else
#include "../interface/console.h"
#include "../interface/midi_io.h"
#include <unistd.h>
#include <algorithm> // for copy() and assign() 
#include <iterator> // for back_inserter 
#endif

Transport::Transport()
{
    playing = false;
}

void Transport::pulse() 
{
    for (Sequencer* s : sequencers) {
        s->pulse();
    }
}

void Transport::tick() 
{
    for (Sequencer* s : sequencers)
        s->tick();
}

void Transport::start() 
{
    for (Sequencer* s : sequencers)
        s->start();
    playing = true;
    println_to_console("Start");
}

void Transport::stop() 
{
    for (Sequencer* s : sequencers)
        s->stop();
    playing = false;
    // println_to_console("Stop");
}

// Clock

// TODOs
// Clean up unused variables
// Implement RTC once it part arrives
// Implement function for clock retrieval

Clock::Clock()
{
    internal = true;
    transport = Transport();
    if (internal) {
        BPM = 120.0;
        calc_miliseconds();
    }
    estimated_BPM = 0.0;

    midi_time = -1.0;

    ticks = 0;
    pulses = 0;
    time_since_pulse = 0.0;
    time_since_tick = 0.0;
}

void Clock::register_sequencer(Sequencer* sequencer) 
{
    transport.sequencers.push_back(sequencer);
}

#ifndef ARDUINO
void Clock::register_update_sequencer(Sequencer* sequencer)
{
    transport.update_sequencers.push_back(sequencer);
}

void Clock::clear_update_sequencers()
{
    transport.cycle_refresh = false;
    transport.update_sequencers.clear();
}

void Clock::set_cycle_update(int bars)
{
    transport.cycle_refresh = true;
    transport.cycle_pulses = bars*PULSES_PER_BAR;

    println_to_console("cycle set");

    if (!transport.playing) { //can update immediately if transport is not playing
        cycle_update();
    } 
        
}

void Clock::cycle_update()
{

    for (Sequencer *s : transport.sequencers) // Deallocate memory of old sequencers
        delete s;
    transport.sequencers.clear();

    transport.sequencers = transport.update_sequencers; // Replaces the sequencers

    transport.update_sequencers.clear();
    transport.cycle_refresh = false;

    println_to_console("cycle updated");
    println_to_console("--------------");

    if (transport.playing) { // Need to kick off the sequencer start code
        for (Sequencer* s : transport.sequencers)
            s->start();
    }
    // for (Sequencer *s : transport.sequencers) {
    //     s->dump_to_console();
    // }

}
#endif

void Clock::pulse() 
{
    time_since_pulse = 0.0;
    if (internal) {
        send_midi_pulse();
    } 
    else { //Internal clock runs on ticks, external runs on pulses
        
        if (!transport.playing) // If external clock, don't pulse unless transport is playing
            return;

        transport.pulse(); 
        double delta_time = update_time();
        estimate_BPM(delta_time);
    }
        
    pulses++;

    #ifndef ARDUINO
    if (transport.cycle_refresh && (pulses % transport.cycle_pulses == 0)) {
        cycle_update();
    }
    #endif // ! ARDUINO
    
        
}

inline void Clock::tick() 
{ // This is only active on internal clock
    transport.tick();
    time_since_tick = 0.0;
    if (ticks % TICKS_PER_PULSE == 0)
        pulse();
    ticks++;
}

void clock_loop() 
{
    while (true) {    
        double delta = midiclock->update_time();
        if (midiclock->internal) {
            if (midiclock->transport.playing)
                if (midiclock->time_since_tick >= midiclock->ms_per_tick)
                    midiclock->tick();
        } else {
            // TODO handle external clock
            // Check for midi clock in
        }
    }
}
// #endif

inline double Clock::update_time() {

    #ifdef ARDUINO
    unsigned long now = micros();
    double delta_time = (now - time)/1000.0;
    #else
    using namespace std::chrono;
    high_resolution_clock::time_point now = high_resolution_clock::now();
    duration<double, std::milli> milliseconds = now - time;
    double delta_time = milliseconds.count();
    #endif

    if (midi_time >= 0) { 
        midi_time += delta_time;
        time_since_tick += delta_time;
        time_since_pulse += delta_time;
    } else { // If clock just started, set values to zero
        delta_time = 0.0;
        midi_time = 0.0;
        time_since_tick = 0.0;
    }

    time = now;
    return delta_time;
}

void Clock::begin_loop()
{
    clock_thread = std::thread(clock_loop);
    clock_thread.detach();
}

void Clock::start() 
{
    transport.start();
    if (internal) {
        // println_to_console("internal");
        // println_to_console(ms_per_tick);

        tick();

    } else {
        // TODO: enable ticks with external clock
        // println_to_console("external");

        // pulse();
    }
}

void Clock::stop() 
{
    if (!transport.playing) 
        return;
    
    transport.stop();
    midi_time = -1.0; // Workaround to ensure 
    ticks = 0;
    pulses = 0;

    #ifndef ARDUINO
    if (transport.cycle_refresh) {
        println_to_console("attempting update - stop");
        cycle_update();
    }
    #endif
}

void Clock::calc_miliseconds(double bpm) 
{
    if (bpm == 0.0)
        bpm = BPM;
    ms_per_pulse = MS_PER_MIN/(bpm*PPQ);
    ms_per_tick = ms_per_pulse / TICKS_PER_PULSE;
}

void Clock::estimate_BPM(double delta_time) 
{
    if (delta_time > 0) {
        if (estimated_BPM == 0.0)
            estimated_BPM = MS_PER_MIN/(time_since_pulse)*PPQ;
        else
            estimated_BPM = 0.5 * (estimated_BPM + MS_PER_MIN/(time_since_pulse*PPQ));
        calc_miliseconds(estimated_BPM);
        // println_to_console(estimated_BPM);
    } 
}
