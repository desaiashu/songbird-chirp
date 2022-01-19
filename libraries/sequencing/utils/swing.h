#ifndef UTILS_SWING
#define UTILS_SWING

#include "time_constants.h"

enum amount {
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

struct Swing {

        int base;
        double adjustment;
        bool human;
    
        Swing(int amount=STRAIGHT, int base=dur::x, bool human=false);
        int adjust(int ticks);
};

#endif // UTILS_SWING