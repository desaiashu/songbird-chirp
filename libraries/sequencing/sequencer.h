#ifndef SEQUENCING_SEQUENCER
#define SEQUENCING_SEQUENCER

#ifdef FEATHER
#include <scale.h>
#else
#include "../theory/scale.h"
#endif


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

#endif // SEQUENCING_SEQUENCER