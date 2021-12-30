#ifndef SEQUENCING_SEQUENCER
#define SEQUENCING_SEQUENCER

#ifdef ARDUINO
#include <scale.h>
#else
#include "../theory/scale.h"
#endif

class Sequencer {
    private:

    public:
        Sequencer(Scale scale, int channel);
        Scale scale;
        int channel;
        void pulse();
        void tick();
        void start();
        void stop();
        void change_scale(Scale new_scale);
};

// Includes for convenience of other classes
#include "bass.h"
#include "groove.h"
#include "melody.h"
#include "patterns.h"
#include "file_sequencer.h"

#endif // SEQUENCING_SEQUENCER