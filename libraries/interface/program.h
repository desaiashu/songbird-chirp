#ifndef INTERFACE_PROGRAM
#define INTERFACE_PROGRAM

#ifdef ARDUINO
#include <composer.h>
#include <electronica_composer.h>
#include <midi_effects.h>
#include <display.h>
#else
#include "../composition/composer.h"
#include "../effects/midi_effects.h"
#endif

const int basic_program = 0;
const int midi_file_program = 1;
const int dance_loop_program = 2;
const int electronica_program = 3;
const int effects_program = 4;

class Program {
    private:
        int program_index;

    Composer composer;

    Display disp;

    public:
        Program(int program_index, Display& d);
        void initialize_effects();
        void button_callback(int button);
};

#endif // INTERFACE_PROGRAM