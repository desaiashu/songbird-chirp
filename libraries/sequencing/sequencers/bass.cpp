// #plucky, driving, full, low
#include "bass.h"

BassSequencer::BassSequencer(Progression progression, int channel, sequencer_style style) : Sequencer(progression, channel), style(style)
{
    pulses = -1;
    step = 0;
    progression_step = 0;
    pulses_per_step = 6*progression.cadence;
    pulses_per_progression_step = 96*progression.cadence;
}

void BassSequencer::pulse()
{
    pulses += 1;
    if (pulses % pulses_per_step == 0) {

        if (pulses % pulses_per_progression_step == 0)
            progression_step = (progression_step + 1) % progression.chords.size();
        
        int note = progression.chords[progression_step].bass;

        instrument.start_note(note, 100);
        last_note = note;

    } else if (pulses % pulses_per_step == 3) {
        instrument.end_note(last_note);
    }
}

void BassSequencer::stop() 
{
    step = -1;
}