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

        Chord chord;
        arp_type type;
        int octaves;
    
        Arpeggiator(Chord chord, arp_type type=NOTE, int octaves=0);
        Arpeggiator(int note=0, int octaves=0) : Arpeggiator(Chord(Scale(note)), NOTE, octaves) {};
        pair<int, double> note_for_step(int step);

};

#endif // ARPEGGIATIONS