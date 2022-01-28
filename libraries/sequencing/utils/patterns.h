#ifndef PATTERNS
#define PATTERNS

#include "../note.h"
#include <vector>
using std::vector;

const int e_pattern[32] = {2,7,1,8,2,8,1,8,2,8,4,5,9,0,4,5,2,3,5,3,6,0,2,8,7,4,7,1,3,5,2,7};

//Common patterns
static vector<int> whole_notes {w};
static vector<int> triplet_quarter {qt,qt,qt};
static vector<int> rolling_bar_bass {x, _x, x, _x, x, _x, x, _x, x, _x, x, _x, x, _x, x, _x, _c};
//Might want to allow custom timing for this
//Need to deal with variable timing, but also deal with chord patterns with changes at diff points

//Common percussive patterns
static vector<int> four_on_floor {xx,_xx};
static vector<int> off_beat_hat {_xx,xx};
static vector<int> two_four_clap {_q,xx,_xx};
static vector<int> sixteenth_shaker {x};
static vector<int> tom_pattern {_q,_q,_q,_q,_q,q,_q,q,_q,_q,_q,_q,_q,_q,_q,_q};

//Chord patterns
static vector<int> one_bar_chords {w, _c};

#endif // PATTERNS