#ifndef ARDUINO

#include "libraries/interface/console.h"
#include "libraries/sequencing/clock.h"
#include "libraries/interface/midi_io.h"
#include "libraries/interface/program.h"
#include "tests.cpp"
#include <unistd.h>

// Clock* midiclock;
Program* program;
Display* display = new Display();

int main()
{
    println_to_console("Chirp Chirp");

    midiclock->internal = false;
    intialize_midi();

    program = new Program(live_program, display);

    // program = new Program(effects_program);

    // test_progression();
    // test_scale();


    midiclock->begin_loop();
    // midiclock->start();

    // Keep program alive
    while(true) {
        sleep(1000);
    }

}

#endif