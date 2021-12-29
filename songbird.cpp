#ifndef ARDUINO

#include "libraries/interface/console.h"
#include "libraries/clock/clock.h"
#include "libraries/interface/midi_io.h"
#include "tests.cpp"

// Clock* midiclock;

int main()
{
    println_to_console("Chirp Chirp");

    test_scale();

    midiclock->internal = false;
    intialize_midi();
    // midiclock->start();

}

#endif