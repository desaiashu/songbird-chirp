#ifndef ARPEGGIATIONS
#define ARPEGGIATIONS

#include <utility>
using std::pair;
#ifdef ARDUINO
#include <chord.h>
#else
#include "../../theory/chord.h"
#endif

struct Arpeggiator {

        Chord chord;
        arp_type type;
        int octaves;
    
        Arpeggiator(Chord chord, arp_type type, int octaves=0);
        pair<int, double> note_for_step(int step);

};

enum arp_type {
    up,
    down,
    up_down,
    poly_random,
};

#endif // ARPEGGIATIONS