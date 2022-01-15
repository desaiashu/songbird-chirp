#include "chord_sequencer.h"

ChordSequencer::ChordSequencer(Progression progression, int channel) : Sequencer(progression, channel)
{
    pulses = -1;
    step = 0;
    pulses_per_step = 96*progression.cadence;
}

void ChordSequencer::pulse()
{
    pulses += 1;
    if (pulses % pulses_per_step == 0) {
        int last = step-1;
        if (last < 0)
            last = progression.chords.size() - 1;
        
        Chord last_chord = progression.chords[last];
        for (int note : last_chord.notes) {
            instrument.end_note(note);
        }
        
        Chord next_chord = progression.chords[step];
        for (int note : next_chord.notes) {
            instrument.start_note(note, 30);
        }
        step = (step + 1) % progression.chords.size();
    }
}

void ChordSequencer::stop() 
{
    step = -1;
}