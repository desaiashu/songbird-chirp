#ifndef NOTES_NOTE
#define NOTES_NOTE

#include <string> 
using std::string;
#include <utility>
using std::pair;

#ifdef ARDUINO
#include <time_constants.h>
#else
#include "../../clock/time_constants.h"
#endif

static const int NOTES_PER_OCTAVE = 12;
enum ticks {
        DOUBLE_NOTE_TICKS = TICKS_PER_BAR*2,
        WHOLE_NOTE_TICKS = TICKS_PER_BAR,
        HALF_NOTE_TICKS = TICKS_PER_BAR/2,
        QUARTER_NOTE_TICKS = TICKS_PER_BAR/4,
        EIGHTH_NOTE_TICKS = TICKS_PER_BAR/8,
        SIXTEETH_NOTE_TICKS = TICKS_PER_BAR/16
};

struct Note {

        int note;
        int velocity;
        int tick;
        bool on;
    
        Note(int note, bool on, int velocity, int tick);

        bool operator< (const Note &other) const { return tick < other.tick; }   
        string name() { return "Note: " + std::to_string(note) + " On: " + std::to_string(on) + " Vel: " + std::to_string(velocity); };

};

static Note noteOn(int note, int velocity, int tick) { return Note(note, true, velocity, tick); };
static Note noteOff(int note, int tick) { return Note(note, false, 0, tick); };

static pair<Note, Note> double_note(int note, int velocity, int tick) { return {noteOn(note, velocity, tick), noteOff(note, tick+DOUBLE_NOTE_TICKS)}; };
static pair<Note, Note> whole_note(int note, int velocity, int tick) { return {noteOn(note, velocity, tick), noteOff(note, tick+WHOLE_NOTE_TICKS)}; };
static pair<Note, Note> half_note(int note, int velocity, int tick) { return {noteOn(note, velocity, tick), noteOff(note, tick+HALF_NOTE_TICKS)}; };
static pair<Note, Note> quarter_note(int note, int velocity, int tick) { return {noteOn(note, velocity, tick), noteOff(note, tick+QUARTER_NOTE_TICKS)}; };
static pair<Note, Note> eighth_note(int note, int velocity, int tick) { return {noteOn(note, velocity, tick), noteOff(note, tick+EIGHTH_NOTE_TICKS)}; };
static pair<Note, Note> sixteenth_note(int note, int velocity, int tick) { return {noteOn(note, velocity, tick), noteOff(note, tick+SIXTEETH_NOTE_TICKS)}; };

static int double_rest() { return DOUBLE_NOTE_TICKS; };
static int whole_rest() { return WHOLE_NOTE_TICKS; };
static int half_rest() { return HALF_NOTE_TICKS; };
static int quarter_rest() { return QUARTER_NOTE_TICKS; };
static int eighth_rest() { return EIGHTH_NOTE_TICKS; };
static int sixteenth_rest() { return SIXTEETH_NOTE_TICKS; };

const int number_from_note(const string note, const int octave);
const string note_from_number(const int num);

#endif // NOTES_NOTE