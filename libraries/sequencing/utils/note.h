#ifndef NOTES_NOTE
#define NOTES_NOTE

#define NOTES_PER_OCTAVE 12

#include <string> 
using std::string;

struct Note {

        int note;
        int velocity;
        int tick;
        bool on;
    
        Note(int note, bool on, int velocity, int tick);

        bool operator< (const Note &other) const { return tick < other.tick; }   
        string name() { return "Note: " + std::to_string(note) + " On: " + std::to_string(on) + " Vel: " + std::to_string(velocity); };

};

static Note noteOn(int note, int velocity, int tick);
static Note noteOff(int note, int tick);

const int number_from_note(const string note, const int octave);
const string note_from_number(const int num);

#endif // NOTES_NOTE