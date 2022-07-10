#ifndef ARPEGGIATIONS
#define ARPEGGIATIONS

#include <utility>
using std::pair;
#ifdef ARDUINO
#include <chord.h>
#else
#include "../../theory/chord.h"
#endif

enum arp_type {
    NOTE,
    UP,
    DOWN,
    UP_DOWN,
    POLY_RANDOM,
};

struct Arpeggiator {

        arp_type type;
        int octaves;
    
        Arpeggiator(arp_type type=NOTE, int octaves=0);
        //Need a way to set single note for arpeggiator?
        // Arpeggiator(int note=0, int octaves=0) : Arpeggiator(NOTE, octaves) {};
        pair<int, double> note_for_step(Chord chord, int step);

};

#endif // ARPEGGIATIONS