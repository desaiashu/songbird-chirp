#ifndef CLOCK_CLOCK
#define CLOCK_CLOCK

#include "time_constants.h"

#ifdef ARDUINO
#include <sequencer.h>
#else
#include "../sequencing/sequencer.h"
#endif

#include <thread>
#include <vector>
using std::vector;

struct Transport {
        bool playing;
        vector<Sequencer*> sequencers;

        // Not sure how to implement callbacks...
        // std::function<void()> step_callback();

        Transport();
        inline void pulse();
        inline void tick();
        inline void start();
        inline void stop();
};

class Clock {
    private:
        
        double ms_per_pulse;
        
        int delta_ms;
        int ticks;
        inline void calc_miliseconds(double bpm=0.0);
        inline void estimate_BPM(double delta_time);
        std::thread clock_thread;
        Clock();

    public:
        
        bool internal;
        double BPM;
        double estimated_BPM;
        int pulses;
        double ms_per_tick;
        double midi_time;
        double time_since_pulse;
        double time_since_tick;

        #ifdef ARDUINO
        unsigned long time;
        #else
        std::chrono::high_resolution_clock::time_point time;
        #endif

        Transport transport;
        static Clock& getInstance()
        {
            static Clock instance;
            return instance;
        }
        
        void register_sequencer(Sequencer* sequencer);
        // void set_transport_callback(void func());
        inline double update_time();
        void pulse();
        inline void tick();
        void start();
        void stop();
};

#ifndef MIDI_CLOCK
#define MIDI_CLOCK
static Clock* midiclock = &Clock::getInstance();
#endif // !MIDI_CLOCK


#endif // CLOCK_CLOCK