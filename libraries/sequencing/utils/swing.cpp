#include "swing.h"
#include <cstdlib>

Swing::Swing(int amount, int base, bool human) 
    : adjustment(amount / 100.0), base(base), human(human)
{
    
}

int Swing::adjust(int ticks) 
{
    // May want to consider different formulas for swing where things don't move as much
    int offset = ticks % (base*2);

    // 0 1 2 3 4 5 6 7 8 9      base = 5
    // 0 1 2 3 4 5 6 7 8 9 <- 9 moves most
    // 0 1 2 3 4 5 6 7 8 9 -> 9 moves least
    // 0 9 8 7 6 5 4 3 2 1      values after change

    if (adjustment > 0) {
        offset = (base*2 - offset) % (base*2); // If dragging, higher tick values should move less
    }
    ticks += offset*adjustment; // Dragging is positive, rushing is negative 
    
    if (human) {
        ticks += (rand() % 3)-1;
        ticks += (rand() % 3)-1;
    }

    return ticks;
}
