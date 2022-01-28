#include "chord_sequencer.h"

ChordSequencer::ChordSequencer(Progression progression, int bar_length, int channel) : Sequencer(progression, bar_length, channel)
{
    gen_chord_sequence(progression, 100, one_bar_chords);
}
