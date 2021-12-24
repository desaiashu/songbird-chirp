#ifndef ARDUINO

#include "libraries/interface/console.h"
#include "libraries/clock/clock.h"
#include "libraries/interface/midi_io.h"

int main()
{
    print_to_console("Chirp Chirp");

    intialize_midi();
    Transport* transport = new Transport();
    
}

#endif