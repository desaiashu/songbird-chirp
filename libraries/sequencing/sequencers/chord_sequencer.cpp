#include "chord_sequencer.h"

ChordSequencer::ChordSequencer(Progression progression, int bar_length, int channel) : Sequencer(progression, bar_length, channel)
{
    chord_pattern();

    sort(notes.begin(), notes.end());
}

void ChordSequencer::chord_pattern()
{
    for (size_t i = 0; i < bar_length; i++)
    {
        int ticks = i*TICKS_PER_BAR;
        Chord chord = progression.chords[i];

        for (int note : chord.notes) {
            pair<Note, Note> note_pair = whole_note(note, 100, ticks);
            append_note(note_pair);
        }
    }
}