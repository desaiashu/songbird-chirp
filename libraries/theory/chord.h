#ifndef THEORY_CHORD
#define THEORY_CHORD

#include "scale.h"
#include <string>
using std::string;
#include <vector>
using std::vector;

struct Chord {
        
        vector<int> notes;
        int bass;

        Scale scale;
        int degree;
        int inversion;
        bool harmonic;
        bool seventh;
        bool fifth;

        //Create chord
        Chord(Scale scale=Scale(), int degree=0, int inversion=0, bool seventh=false, bool harmonic=false, bool fifth=true);

        //Generate next chord based on prior chord
        //Currently following classical music rules
        Chord(Chord chord, int degree, bool seventh=false, bool harmonic=false);

        // May want to create chord from name later
        // Chord(string root_note="C", string triad="minor", int inversion=0, string seventh="none");
        
        string name();

};

#endif // THEORY_CHORD