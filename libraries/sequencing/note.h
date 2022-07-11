#ifndef UTILS_NOTE
#define UTILS_NOTE

#include <string> 
using std::string;
#include <utility>
using std::pair;

#ifdef ARDUINO
#include <time_constants.h>
#else
#include "utils/time_constants.h"
#endif

static const int NOTES_PER_OCTAVE = 12;

struct Note {

        int note;
        int velocity;
        int tick;
        bool on;
    
        Note(int note, bool on, int velocity, int tick);

        bool operator< (const Note &other) const { return tick < other.tick; }   
        string name() { return "Note: " + std::to_string(note) + " On: " + std::to_string(on) + " Vel: " + std::to_string(velocity); };

};

static Note note_on(int note, int velocity, int tick) { return Note(note, true, velocity, tick); };
static Note note_off(int note, int tick) { return Note(note, false, 0, tick); };

static pair<Note, Note> gen_note(int note, int note_length, int velocity, int tick) { return {note_on(note, velocity, tick), note_off(note, tick+note_length)}; };
static int rest(int note_length) { return note_length; };

const int number_from_note(const string note, const int octave);
const string note_from_number(const int num);

#endif // UTILS_NOTE