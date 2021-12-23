#ifndef CLOCK_CLOCK
#define CLOCK_CLOCK

#include <sequencer.h>

#define MAX_SEQUENCERS 20

class Transport {
    private:
        bool playing = false;
        Sequencer* sequencers[MAX_SEQUENCERS];

    public:
        Transport();
        void pulse();
        void tick();
        void start();
        void stop();
};

#endif