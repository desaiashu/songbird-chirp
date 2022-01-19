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
    println_to_console("Stop");
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

void Clock::pulse() 
{
    time_since_pulse = 0.0;
    if (internal) {
        send_midi_pulse();
    } 
    else {
        //Only pulse if not ticking
        transport.pulse();
        double delta_time = update_time();
        estimate_BPM(delta_time);
    }
        
    pulses+=1;
}

inline void Clock::tick() 
{
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

void Clock::start() 
{
    transport.start();
    if (internal) {
        println_to_console("internal");
        println_to_console(ms_per_tick);

        clock_thread = std::thread(clock_loop);
        clock_thread.join();

        tick();

    } else {
        // TODO: enable ticks with external clock
    }
}

void Clock::stop() 
{
    clock_thread.~thread();
    transport.stop();
    midi_time = -1.0; // Workaround to ensure 
    ticks = 0;
    pulses = 0;
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





// void clock_start(std::function<void(void)> func, unsigned int interval)
// {
//   std::thread([func, interval]()
//   { 
//     while (true)
//     { 
//       auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
//       func();
//       std::this_thread::sleep_until(x);
//     }
//   }).detach();
// }

// import time
// from songbird.interface.midi import midi
// from songbird.sequencing.sequencer import Sequencer
// from adafruit_midi.start import Start
// from adafruit_midi.stop import Stop
// from adafruit_midi.timing_clock import TimingClock

// class Transport:
//     def __init__(
//         self,
//     ):
//         self.playing = False
//         self.sequencers = []

//     def pulse(self):
//         for sequencer in self.sequencers:
//              sequencer.pulse()

//     def tick(self):
//         for sequencer in self.sequencers:
//              sequencer.tick()

//     def start(self):
//         for sequencer in self.sequencers:
//              sequencer.start()
//         self.playing = True
//         print('start')

//     def stop(self):
//         for sequencer in self.sequencers:
//              sequencer.stop()
//         self.playing = False
//         print('stop')


// # Todos:
// # Rewrite midi clock in c++?
// # Move to raspberry pi?
// # Allow for 48ppq clock? 96ppq clock?

// #PPQ = Pulses per quarter note (1 quarter note = 1 beat)
// PPQ = 24
// NS_PER_MIN = 60000000000
// QUARTER_NOTE_PER_BAR = 4 # This may change later
// TICKS_PER_PULSE = 4 # Assumes 24ppq clock and 96ppq midi files
// TICKS_PER_BAR = TICKS_PER_PULSE*PPQ*QUARTER_NOTE_PER_BAR

// class Clock:

//     def __init__(
//         self,
//         internal = True
//     ):
//         self.internal = internal
//         self.transport = Transport()
//         if internal:
//             self.BPM = 120.0
//             self.calc_miliseconds()
//         # else:
//         #     self.estimated_BPM = 0.0

//         self.estimated_BPM = 0.0

//         self.midi_time = -1.0
//         self.time = 0.0

//         self.ticks = 0
//         self.pulses = 0

//     def register_sequencer(self, sequencer: Sequencer):
//         self.transport.sequencers.append(sequencer)

//     def set_transport_callback(self, callback):
//         self.transport.step_callback = callback

//     def pulse(self):
//         self.transport.pulse()
//         self.time_since_pulse = 0.0
//         # if self.internal:
//         #     midi.send(TimingClock())

//     def tick(self):
//         self.transport.tick()
//         self.time_since_tick = 0.0

//     def start(self):
//         self.transport.start()

//     def stop(self):
//         self.transport.stop()
//         self.midi_time = -1.0


//     def calc_miliseconds(self, bpm=None):
//         if not bpm:
//             bpm = self.BPM
//         self.ns_per_pulse = NS_PER_MIN/(bpm*PPQ)
//         self.ns_per_tick = self.ns_per_pulse / TICKS_PER_PULSE

//     def estimate_bpm(self, delta_ns):
//         if delta_ns > 0:
//             if self.estimated_BPM == 0.0:
//                 self.estimated_BPM = NS_PER_MIN/(self.time_since_pulse*PPQ)
//             else:
//                 self.estimated_BPM = 0.5 * (self.estimated_BPM + NS_PER_MIN/(self.time_since_pulse*PPQ))
//             self.calc_miliseconds(self.estimated_BPM)
//             # print(self.estimated_BPM)

//     def get_midi_and_delta_time(self):
//         current_time = time.monotonic_ns()
//         if self.midi_time >=0:
//             delta_time = (current_time - self.time)
//             self.midi_time += delta_time
//             self.time_since_tick += delta_time
//             self.time_since_pulse += delta_time
//         else:
//             delta_time = 0
//             self.midi_time = 0.0
//             self.time_since_tick = 0.0
//             self.time_since_pulse = 0.0
//         self.time = current_time
//         return delta_time

//     def handler(self):
//         delta = self.get_midi_and_delta_time()
//         if self.internal:
//             if self.transport.playing:
//                 if self.time_since_tick >= self.ns_per_tick:
//                     self.tick()
//                 if self.time_since_pulse >= self.ns_per_pulse:
//                     self.pulse()
//         else:
//             msg = midi.receive()
//             if msg is not None:
//                 if isinstance(message, TimingClock) and self.transport.playing:
//                     self.estimate_bpm(delta)
//                     self.pulse()
//                 elif isinstance(message, Start):
//                     self.start()
//                 elif isinstance(message, Stop):
//                     self.stop()
//             elif self.estimated_BPM > 0:
//                 if self.time_since_tick > self.ns_per_tick:
//                     self.tick()


// clock = Clock()
