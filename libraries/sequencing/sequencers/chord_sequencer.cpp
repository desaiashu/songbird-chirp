#include "chord_sequencer.h"

ChordSequencer::ChordSequencer(Progression p, int sequence_length, int channel) 
            : Sequencer(sequence_length, channel)
{
    progression = p;
    pattern = one_bar_chords;
    gen_chord_sequence(100);
}
