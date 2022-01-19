#ifndef ARDUINO

#include "libraries/interface/console.h"
#include "libraries/sequencing/clock.h"
#include "libraries/interface/midi_io.h"
#include "libraries/interface/program.h"
#include "tests.cpp"

// Clock* midiclock;
Program* program;

int main()
{
    println_to_console("Chirp Chirp");

    program = new Program(electronica_program);

    // test_progression();
    // test_scale();

    midiclock->internal = true;
    intialize_midi();
    midiclock->start();

}

#endif