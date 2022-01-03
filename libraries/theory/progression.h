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
        double cadence;
        Scale scale;

        //Create chord
        //TODO: introduce different styles, eg. Jazz
        //TODO: support multiple or varying progressions
        Progression(Scale scale=Scale(), double cadence=1.0, int length=4, bool seventh=false);

};

#endif // THEORY_PROGRESSION