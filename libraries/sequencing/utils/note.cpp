
#include "note.h"
#include <algorithm>

const string notes[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

Note::Note(int note, bool on, int velocity, int tick) 
    : note(note), on(on), velocity(velocity), tick(tick)
{
    
}

Note noteOn(int note, int velocity, int tick) 
{
    return Note(note, true, velocity, tick);
}

Note noteOff(int note, int tick) 
{
    return Note(note, false, 0, tick);
}

const int number_from_note(const string note, const int octave) 
{
    int index = std::distance(notes,
                               std::find(notes, &notes[12], note));
    return index + (octave+1)*NOTES_PER_OCTAVE;
}

const string note_from_number(const int num) 
{
    return notes[num%NOTES_PER_OCTAVE] + std::to_string(num/NOTES_PER_OCTAVE - 1);
}