#include "program.h"

const int basic = 0;
const int midi_file = 1;
const int dance_loop = 2;
const int electronica = 3;

Program::Program(int program_index) :
    program_index(program_index)
{
    switch(program_index) {
        case basic:
            composer = BasicComposer();
            break;
        case midi_file:
            composer = FileComposer();
            break;
        case dance_loop:
            composer = LoopComposer();
            break;
        case electronica:
            composer = ElectronicaComposer();
            break;
    }
}

// from .display import Display
// from .buttons import Buttons

// # from songbird.composition.basic_composer import BasicComposer
// from songbird.composition.file_composer import FileComposer

// # Display initialization and callback
// display = Display("", "")

// def transport_step_callback(note):
//     pass
//     # display.setLabel2(note)

// # Construct basic handler
// file_composer = FileComposer('midifiles/ableton.mid', transport_step_callback)
// display.setLabel1(file_composer.scale.name())

// # Button initialization, handler, and callback
// def button_1_callback():
//     new = file_composer.change_scale()
//     display.setLabel1(new)

// buttons = Buttons(button_1_callback)

// def handler():
//     buttons.checkClicks()


