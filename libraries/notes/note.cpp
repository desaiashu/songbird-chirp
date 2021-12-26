
#include "note.h"

const string notes[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

const int number_from_note(const string note, const int octave) 
{
    int index = std::distance(notes,
                               std::find(notes, &notes[12], note));
    return index + (octave+1)*NOTES_PER_OCTAVE;
}

const string note_from_number(const int num) 
{
    return notes[num%NOTES_PER_OCTAVE];
}
