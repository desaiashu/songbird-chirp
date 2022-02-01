#ifndef THEORY_SCALE
#define THEORY_SCALE

#include <string>
using std::string;
#include <vector>
using std::vector;

enum scale_degrees {
        THIRD_DEGREE = 2,
        FIFTH_DEGREE = 4,
        SEVENTH_DEGREE = 6,
        OCTAVE_DEGREE = 7,
};

struct Scale {
        
        int root;
        int offset;
        int octave;
        vector<int> dissonants;
        vector<int> notes;
        string mode;
        string type;
        string root_note;

        Scale(string root_note="C", int octave=4, string mode="minor", string type="base");
        Scale(int root, string mode="minor", string type="base");
        string name();
        void gen_scale(bool base=true);
        void gen_wide_scale();
        int note_degree(int note);

};

#endif // THEORY_SCALE