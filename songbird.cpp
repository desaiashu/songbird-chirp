#ifndef ARDUINO

#include "libraries/interface/console.h"
#include "libraries/clock/clock.h"

int main()
{
    print_to_console("Chirp Chirp");

    Transport* transport = new Transport();
}

#endif