#ifndef ARDUINO

#include "libraries/interface/console.h"
#include "libraries/clock/clock.h"
#include "libraries/interface/midi_io.h"
#include "tests.cpp"

int main()
{
    print_to_console("Chirp Chirp");

    test_notes();

    intialize_midi();
    
}

#endif