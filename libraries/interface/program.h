#ifndef INTERFACE_PROGRAM
#define INTERFACE_PROGRAM

#ifdef ARDUINO
#include <composer.h>
#include <electronica_composer.h>
#else
#include "../composition/composer.h"
#endif

const int basic_program = 0;
const int midi_file_program = 1;
const int dance_loop_program = 2;
const int electronica_program = 3;

class Program {
    private:
        int program_index;

    Composer composer;

    public:
        Program(int program_index);
};

#endif // INTERFACE_PROGRAM