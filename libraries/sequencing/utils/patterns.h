#ifndef PATTERNS
#define PATTERNS

#include "../note.h"

const int e_pattern[32] = {2,7,1,8,2,8,1,8,2,8,4,5,9,0,4,5,2,3,5,3,6,0,2,8,7,4,7,1,3,5,2,7};

//Common patterns
static vector<int> whole_notes {w};
static vector<int> triplet_quarter {qt,qt,qt};
static vector<int> rolling_bass {x, _x};

//Common percussive patterns
static vector<int> four_on_floor {xx,_xx};
static vector<int> off_beat_hat {_xx,xx};
static vector<int> two_four_clap {_q,xx,_xx};
static vector<int> sixteenth_shaker {x};


#endif // PATTERNS