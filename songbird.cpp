#ifndef ARDUINO

#include "libraries/interface/console.h"
#include "libraries/clock/clock.h"
#include "libraries/interface/midi_io.h"
#include "tests.cpp"

int main()
{
    println_to_console("Chirp Chirp");

    test_scale();

    intialize_midi();
    
}

#endif