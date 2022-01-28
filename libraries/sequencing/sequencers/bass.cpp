// #plucky, driving, full, low
#include "bass.h"

BassSequencer::BassSequencer(Progression progression, int bar_length, int channel, sequencer_style style) : Sequencer(progression, bar_length, channel), style(style)
{
    gen_chord_sequence(progression, 100, rolling_bar_bass, Swing(DRAG_10, dur::xx, true), true);
}
