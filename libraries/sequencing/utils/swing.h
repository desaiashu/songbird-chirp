#ifndef UTILS_SWING
#define UTILS_SWING

#include "time_constants.h"

struct Swing {

        int base;
        double adjustment;
        bool human;
    
        Swing(int amount=STRAIGHT, int base=dur::x, bool human=false);
        int adjust(int ticks);
};

#endif // UTILS_SWING