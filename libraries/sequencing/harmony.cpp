#include "harmony.h"

HarmonySequencer::HarmonySequencer(Progression p, int sequence_length, int channel, sequencer_style style) 
    : Sequencer(sequence_length, channel), style(style)
{
    progression = p;
    pattern = triplet_quarter;
    arp = Arpeggiator(UP_DOWN, 1);
    gen_arp_sequence(30);
}
