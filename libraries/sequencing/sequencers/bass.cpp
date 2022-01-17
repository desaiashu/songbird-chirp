// #plucky, driving, full, low
#include "bass.h"

BassSequencer::BassSequencer(Progression progression, int bar_length, int channel, sequencer_style style) : Sequencer(progression, bar_length, channel), style(style)
{
    bass_pattern();
}

void BassSequencer::bass_pattern()
{
    for (size_t i = 0; i < bar_length; i++)
    {
        int ticks = i*TICKS_PER_BAR;
        Chord chord = progression.chords[i];
        
        for (size_t j = 0; j < 8; j++) {

            pair<Note, Note> note_pair = sixteenth_note(chord.bass, 100, ticks);
            ticks = append_note(note_pair);
            
            ticks += sixteenth_rest();
        }
    }
}
