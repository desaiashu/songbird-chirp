// #plucky, driving, full, low
#include "bass.h"

BassSequencer::BassSequencer(Progression p, int sequence_length, int channel, sequencer_style style) : Sequencer(sequence_length, channel), style(style)
{
    progression = p;
    pattern = rolling_bar_bass;
    swing = Swing(DRAG_10, dur::xx, true);
    gen_chord_sequence(100, true);
}
