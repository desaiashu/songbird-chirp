#ifndef TIME_CONSTANTS
#define TIME_CONSTANTS

// PPQ = Pulses per quarter note (1 quarter note = 1 beat)
static const int PPQ = 24;
static const int MS_PER_MIN = 60000;
static const int QUARTER_NOTE_PER_WHOLE_NOTE = 4; 
static const int TICKS_PER_PULSE = 4; // Assumes 24ppq clock and 96ppq midi files
static const int TICKS_PER_WHOLE_NOTE = TICKS_PER_PULSE*PPQ*QUARTER_NOTE_PER_WHOLE_NOTE;

static const int TICKS_PER_BAR = TICKS_PER_WHOLE_NOTE; // This may change later w/ diff time signatures

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

#endif // TIME_CONSTANTS