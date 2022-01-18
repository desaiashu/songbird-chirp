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
enum dur {
        ww = TICKS_PER_WHOLE_NOTE*2,
        w = TICKS_PER_WHOLE_NOTE,
        qq = TICKS_PER_WHOLE_NOTE/2,
        q = TICKS_PER_WHOLE_NOTE/4,
        xx = TICKS_PER_WHOLE_NOTE/8,
        x = TICKS_PER_WHOLE_NOTE/16,
        wwd = TICKS_PER_WHOLE_NOTE*2 *3/2,
        wd = TICKS_PER_WHOLE_NOTE *3/2,
        qqd = TICKS_PER_WHOLE_NOTE/2 *3/2,
        qd = TICKS_PER_WHOLE_NOTE/4 *3/2,
        xxd = TICKS_PER_WHOLE_NOTE/8 *3/2,
        xd = TICKS_PER_WHOLE_NOTE/16 *3/2,
        wwt = TICKS_PER_WHOLE_NOTE*2 *2/3,
        wt = TICKS_PER_WHOLE_NOTE *2/3,
        qqt = TICKS_PER_WHOLE_NOTE/2 *2/3,
        qt = TICKS_PER_WHOLE_NOTE/4 *2/3,
        xxt = TICKS_PER_WHOLE_NOTE/8 *2/3,
        xt = TICKS_PER_WHOLE_NOTE/16 *2/3,
        _ww = -TICKS_PER_WHOLE_NOTE*2,
        _w = -TICKS_PER_WHOLE_NOTE,
        _qq = -TICKS_PER_WHOLE_NOTE/2,
        _q = -TICKS_PER_WHOLE_NOTE/4,
        _xx = -TICKS_PER_WHOLE_NOTE/8,
        _x = -TICKS_PER_WHOLE_NOTE/16,
        _wwd = -TICKS_PER_WHOLE_NOTE*2 *3/2,
        _wd = -TICKS_PER_WHOLE_NOTE *3/2,
        _qqd = -TICKS_PER_WHOLE_NOTE/2 *3/2,
        _qd = -TICKS_PER_WHOLE_NOTE/4 *3/2,
        _xxd = -TICKS_PER_WHOLE_NOTE/8 *3/2,
        _xd = -TICKS_PER_WHOLE_NOTE/16 *3/2,
        _wwt = -TICKS_PER_WHOLE_NOTE*2 *2/3,
        _wt = -TICKS_PER_WHOLE_NOTE *2/3,
        _qqt = -TICKS_PER_WHOLE_NOTE/2 *2/3,
        _qt = -TICKS_PER_WHOLE_NOTE/4 *2/3,
        _xxt = -TICKS_PER_WHOLE_NOTE/8 *2/3,
        _xt = -TICKS_PER_WHOLE_NOTE/16 *2/3,
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

static Note note_on(int note, int velocity, int tick) { return Note(note, true, velocity, tick); };
static Note note_off(int note, int tick) { return Note(note, false, 0, tick); };

static pair<Note, Note> gen_note(int note, int note_length, int velocity, int tick) { return {note_on(note, velocity, tick), note_off(note, tick+note_length)}; };
static int rest(int note_length) { return note_length; };

const int number_from_note(const string note, const int octave);
const string note_from_number(const int num);

#endif // NOTES_NOTE