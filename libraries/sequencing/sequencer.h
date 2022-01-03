#ifndef SEQUENCING_SEQUENCER
#define SEQUENCING_SEQUENCER

#ifdef ARDUINO
#include <scale.h>
#include <instrument.h>
#include <progression.h>
#else
#include "../theory/scale.h"
#include "../theory/progression.h"
#include "../voices/instrument.h"
#endif

enum sequencer_style {
    proggy, groovy, sustained, arp, accent
};

class Sequencer {
    private:

    public:
        Sequencer(Progression progression, int channel);
        Scale scale;
        Progression progression;
        Instrument instrument;
        virtual void pulse();
        virtual void tick();
        virtual void start();
        virtual void stop();
        void change_scale(Scale new_scale);
};

// Includes for convenience of other classes
#include "bass.h"
#include "groove.h"
#include "melody.h"
#include "patterns.h"
#include "file_sequencer.h"
#include "chord_sequencer.h"
#include "harmony.h"

#endif // SEQUENCING_SEQUENCER