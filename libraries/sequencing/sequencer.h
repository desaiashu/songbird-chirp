#ifndef SEQUENCING_SEQUENCER
#define SEQUENCING_SEQUENCER

#include <Scale.h>

class Sequencer {
    private:
        bool playing = false;
        Scale *scale;
        int note;
        int root;

    public:
        Sequencer();
        void changeScale(Scale* scale);
        void pulse();
        void tick();
        void start();
        void stop();
};

#endif