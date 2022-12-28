#ifndef TIME_CONSTANTS
#define TIME_CONSTANTS

// #include <map>
// using namespace std;

#include <string>
using std::string;

// PPQ = Pulses per quarter note (1 quarter note = 1 beat)
static const int PPQ = 24;
static const int MS_PER_MIN = 60000;
static const int QUARTER_NOTE_PER_WHOLE_NOTE = 4; 
static const int TICKS_PER_PULSE = 4; // Assumes 24ppq clock and 96ppq midi files
static const int TICKS_PER_WHOLE_NOTE = TICKS_PER_PULSE*PPQ*QUARTER_NOTE_PER_WHOLE_NOTE;

static const int TICKS_PER_BAR = TICKS_PER_WHOLE_NOTE; // This may change later w/ diff time signatures
static const int PULSES_PER_BAR = TICKS_PER_BAR / TICKS_PER_PULSE;

enum swing_amount {
    STRAIGHT = 0,
    DRAG_10 = 10,
    DRAG_20 = 20,
    DRAG_25 = 25,
    DRAG_33 = 33,
    DRAG_40 = 40,
    RUSH_10 = -10,
    RUSH_20 = -20,
    RUSH_25 = -25,
    RUSH_TRIPLET = -33,
    RUSH_40 = -40,
};

enum dur {
        ww = TICKS_PER_WHOLE_NOTE*2,
        w = TICKS_PER_WHOLE_NOTE,
        qq = TICKS_PER_WHOLE_NOTE/2,
        q = TICKS_PER_WHOLE_NOTE/4,
        xx = TICKS_PER_WHOLE_NOTE/8,
        x = TICKS_PER_WHOLE_NOTE/16,
        wwd = TICKS_PER_WHOLE_NOTE*2 *3/2,
        wd = TICKS_PER_WHOLE_NOTE *3/2,
        qqd = TICKS_PER_WHOLE_NOTE/2 *3/2,
        qd = TICKS_PER_WHOLE_NOTE/4 *3/2,
        xxd = TICKS_PER_WHOLE_NOTE/8 *3/2,
        xd = TICKS_PER_WHOLE_NOTE/16 *3/2,
        wwt = TICKS_PER_WHOLE_NOTE*2 *2/3,
        wt = TICKS_PER_WHOLE_NOTE *2/3,
        qqt = TICKS_PER_WHOLE_NOTE/2 *2/3,
        qt = TICKS_PER_WHOLE_NOTE/4 *2/3,
        xxt = TICKS_PER_WHOLE_NOTE/8 *2/3,
        xt = TICKS_PER_WHOLE_NOTE/16 *2/3,
        _ww = -TICKS_PER_WHOLE_NOTE*2,
        _w = -TICKS_PER_WHOLE_NOTE,
        _qq = -TICKS_PER_WHOLE_NOTE/2,
        _q = -TICKS_PER_WHOLE_NOTE/4,
        _xx = -TICKS_PER_WHOLE_NOTE/8,
        _x = -TICKS_PER_WHOLE_NOTE/16,
        _wwd = -TICKS_PER_WHOLE_NOTE*2 *3/2,
        _wd = -TICKS_PER_WHOLE_NOTE *3/2,
        _qqd = -TICKS_PER_WHOLE_NOTE/2 *3/2,
        _qd = -TICKS_PER_WHOLE_NOTE/4 *3/2,
        _xxd = -TICKS_PER_WHOLE_NOTE/8 *3/2,
        _xd = -TICKS_PER_WHOLE_NOTE/16 *3/2,
        _wwt = -TICKS_PER_WHOLE_NOTE*2 *2/3,
        _wt = -TICKS_PER_WHOLE_NOTE *2/3,
        _qqt = -TICKS_PER_WHOLE_NOTE/2 *2/3,
        _qt = -TICKS_PER_WHOLE_NOTE/4 *2/3,
        _xxt = -TICKS_PER_WHOLE_NOTE/8 *2/3,
        _xt = -TICKS_PER_WHOLE_NOTE/16 *2/3,
        _c = 0,
};


static int dur_from_string(string s) { 
    if (s == "ww")
        return ww;
    else if (s == "w")
        return w;
    else if (s == "qq")
        return qq;
    else if (s == "q")
        return q;
    else if (s == "xx")
        return xx;
    else if (s == "x")
        return x;
    else if (s == "wwd")
        return wwd;
    else if (s == "wd")
        return wd;
    else if (s == "qqd")
        return qqd;
    else if (s == "qd")
        return qd;
    else if (s == "xxd")
        return xxd;
    else if (s == "xd")
        return xd;
    else if (s == "wwt")
        return wwt;
    else if (s == "wt")
        return wt;
    else if (s == "qqt")
        return qqt;
    else if (s == "qt")
        return qt;
    else if (s == "xxt")
        return xxt;
    else if (s == "xt")
        return xt;
    else if (s == "_ww")
        return _ww;
    else if (s == "_w")
        return _w;
    else if (s == "_qq")
        return _qq;
    else if (s == "_q")
        return _q;
    else if (s == "_xx")
        return _xx;
    else if (s == "_x")
        return _x;
    else if (s == "_wwd")
        return _wwd;
    else if (s == "_wd")
        return _wd;
    else if (s == "_qqd")
        return _qqd;
    else if (s == "_qd")
        return _qd;
    else if (s == "_xxd")
        return _xxd;
    else if (s == "_xd")
        return _xd;
    else if (s == "_wwt")
        return _wwt;
    else if (s == "_wt")
        return _wt;
    else if (s == "_qqt")
        return _qqt;
    else if (s == "_qt")
        return _qt;
    else if (s == "_xxt")
        return _xxt;
    else if (s == "_xt")
        return _xt;
    else
        return _c;
};

// map<string, int> dur_from_string = {
//     { "ww", ww },
//     { "w", w },
//     { "qq", qq },
//     { "q", q },
//     { "xx", xx },
//     { "x", x },
//     { "wwd", wwd },
//     { "wd", wd },
//     { "qqd", qqd },
//     { "qd", qd },
//     { "xxd", xxd },
//     { "xd", xd },
//     { "wwt", wwt },
//     { "wt", wt },
//     { "qqt", qqt },
//     { "qt", qt },
//     { "xxt", xxt },
//     { "xt", xt },
//     { "_ww", _ww },
//     { "_w", _w },
//     { "_qq", _qq },
//     { "_q", _q },
//     { "_xx", _xx },
//     { "_x", _x },
//     { "_wwd", _wwd },
//     { "_wd", _wd },
//     { "_qqd", _qqd },
//     { "_qd", _qd },
//     { "_xxd", _xxd },
//     { "_xd", _xd },
//     { "_wwt", _wwt },
//     { "_wt", _wt },
//     { "_qqt", _qqt },
//     { "_qt", _qt },
//     { "_xxt", _xxt },
//     { "_xt", _xt },
//     { "_c", _c }
// };

#endif // TIME_CONSTANTS