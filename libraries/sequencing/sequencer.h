#ifndef SEQUENCING_SEQUENCER
#define SEQUENCING_SEQUENCER

#include "note.h"
#include "utils/swing.h"

#ifdef ARDUINO
#include <scale.h>
#include <instrument.h>
#include <progression.h>
#include <console.h>
#else
#include "../theory/scale.h"
#include "../theory/progression.h"
#include "../voices/instrument.h"
#include "../interface/console.h"
#endif

enum sequencer_style {
    proggy, groovy, sustained, arp, accent
};

class Sequencer {
    protected:
        vector<Note> notes;
        vector<Note>::iterator itr;
        int tick_length;
        int bar_length;
        int ticks;
        int append_note(pair<Note, Note> note_pair);
        int adjusted(int ticks, Swing swing);
        //TODOs: extend to support swing, progressions, chords, arpeggiation, velocity modulation, etc
        void gen_sequence(int note, int velocity, vector<int> pattern, Swing swing=Swing(STRAIGHT));
        void gen_sequence(Progression progression, int velocity, vector<int> pattern, Swing swing=Swing(STRAIGHT), bool bass=false);
    public:
        Sequencer(Progression progression, int bar_length, int channel);
        Sequencer(Progression progression, int channel) : Sequencer(progression, 4, channel) {};
        Scale scale;
        Progression progression;
        Instrument instrument;
        virtual void pulse(); //Pulse is only called if using an external clock
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