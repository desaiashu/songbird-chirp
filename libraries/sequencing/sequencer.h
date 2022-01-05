#ifndef SEQUENCING_SEQUENCER
#define SEQUENCING_SEQUENCER

#include "utils/note.h"

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
    protected:
        vector<Note> notes;
        int sequence_tick_length;
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
#include "sequencers/bass.h"
#include "sequencers/groove.h"
#include "sequencers/melody.h"
#include "sequencers/file_sequencer.h"
#include "sequencers/chord_sequencer.h"
#include "sequencers/harmony.h"
#include "utils/patterns.h"
#include "utils/arpeggiator.h"

#endif // SEQUENCING_SEQUENCER