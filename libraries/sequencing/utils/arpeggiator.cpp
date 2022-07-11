#include "arpeggiator.h"

Arpeggiator::Arpeggiator(arp_type type, int octaves) 
                        : type(type), octaves(octaves)
{
    
}

pair<int, double> Arpeggiator::note_for_step(Chord chord, int step) 
{
    int arp_step = step % 6;
    if (arp_step == 4)
        arp_step = 2;
    if (arp_step == 5)
        arp_step = 1;

    return {chord.notes[arp_step]+12, 1};

}
