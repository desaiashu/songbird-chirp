#ifndef THEORY_PROGRESSION
#define THEORY_PROGRESSION

#include "scale.h"
#include "chord.h"
#include <string>
using std::string;
#include <vector>
using std::vector;

struct Progression {
        
        vector<Chord> chords;
        int length;

        //Create chord
        //TODO: introduce different styles, eg. Jazz
        Progression(Scale scale, int length, bool seventh=false);

};

#endif // THEORY_PROGRESSION