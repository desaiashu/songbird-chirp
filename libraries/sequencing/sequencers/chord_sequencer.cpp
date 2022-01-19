#include "chord_sequencer.h"

ChordSequencer::ChordSequencer(Progression progression, int bar_length, int channel) : Sequencer(progression, bar_length, channel)
{
    chord_pattern();

    sort(notes.begin(), notes.end());

    print_to_console("sorted");
}

void ChordSequencer::chord_pattern()
{
    for (size_t i = 0; i < bar_length; i++)
    {
        int ticks = i*TICKS_PER_BAR;
        Chord chord = progression.chords[i];

        println_to_console(chord.name());

        for (int note : chord.notes) {
            pair<Note, Note> note_pair = gen_note(note, dur::w, 100, ticks);
            append_note(note_pair);

            println_to_console(note_pair.first.name());
            println_to_console(note_pair.second.name());
        }
    }
}