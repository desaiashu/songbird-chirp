#ifndef THEORY_SCALE
#define THEORY_SCALE

#include <string>

struct Scale {
        
        int root;
        int offset;
        int octave;
        int dissonants[2];
        std::string mode;
        std::string type;
        std::string root_note;

        std::string name();
        int* genScale();
        int* genWideScale();

};

#endif // THEORY_SCALE