#ifndef ARDUINO

#include "libraries/interface/console.h"
#include "libraries/clock/clock.h"
#include "libraries/interface/midi_io.h"
#include "libraries/interface/program.h"
#include "tests.cpp"

// Clock* midiclock;
Program* program;

int main()
{
    println_to_console("Chirp Chirp");

    program = new Program(basic_program);

    // test_scale();

    midiclock->internal = false;
    intialize_midi();
    // midiclock->start();

    
}

#endif