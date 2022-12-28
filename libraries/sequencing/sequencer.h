#ifndef SEQUENCING_SEQUENCER
#define SEQUENCING_SEQUENCER

#include "note.h"

#ifdef ARDUINO
#include <scale.h>
#include <instrument.h>
#include <progression.h>
#include <console.h>

#include <swing.h>
#include <time_constants.h>
#include <patterns.h>
#include <arpeggiator.h>
#include <modulator.h>
#else
#include "../theory/scale.h"
#include "../theory/progression.h"
#include "../voices/instrument.h"
#include "../interface/console.h"

#include "utils/swing.h"
#include "utils/time_constants.h"
#include "utils/patterns.h"
#include "utils/arpeggiator.h"
#include "utils/modulator.h"
#endif

enum sequencer_style {
    proggy, groovy, sustained, arp, accent
};

class Sequencer {
    protected:
        vector<Note> notes;
        vector<Note>::iterator itr;
        int sequence_length;
        int ticks;
        void append_note(int note, int length, int velocity, int ticks, int step);
        int adjusted_time(int ticks);
        int adjusted_velocity(int velocity, int ticks, int step);
        //TODOs: extend to support swing, progressions, chords, arpeggiation, velocity modulation, etc
        void gen_sequence(int note, int velocity);
        void gen_drum_sequence(int note, int velocity, vector<int> p, Modulator m=NO_MOD, Swing s=Swing());
        void gen_chord_sequence(int velocity, bool bass=false);
        void gen_arp_sequence(int velocity);
    public:
        Sequencer(int sequence_length, int channel);
        Sequencer(int channel=0) : Sequencer(4, channel) {};
        Progression progression;
        vector<int> pattern;
        Arpeggiator arp;
        Modulator mod;
        Swing swing;
        Instrument instrument;
        void gen_notes_sequence(vector<int> notes, vector<int> velocity);
        void set_channel(int channel);
        virtual void pulse(); //Pulse is only called if using an external clock
        virtual void tick();
        virtual void start();
        virtual void stop();
        void change_scale(Scale new_scale);
};

#ifdef ARDUINO
#include <bass.h>
#include <groove.h>
#include <melody.h>
#include <file_sequencer.h>
#include <chord_sequencer.h>
#include <harmony.h>
#else
// Includes for convenience of other classes
#include "sequencers/bass.h"
#include "sequencers/groove.h"
#include "sequencers/melody.h"
#include "sequencers/file_sequencer.h"
#include "sequencers/chord_sequencer.h"
#include "sequencers/harmony.h"
#endif


#endif // SEQUENCING_SEQUENCER