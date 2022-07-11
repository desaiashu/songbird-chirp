#include "program.h"

#if ARDUINO
#include <console.h>
#else
#include "../interface/console.h"
#endif

void initialize_effects() {
    ChordVoicing* chords = new ChordVoicing(8, Scale("C", -1));
    midieffects->register_effect(chords);
}

Program::Program(int program_index) :
    program_index(program_index)
{
    switch(program_index) {
        // case basic_program:
        //     composer = BasicComposer();
        //     break;
        // case midi_file_program:
        //     composer = FileComposer();
        //     break;
        // case dance_loop_program:
        //     composer = LoopComposer();
        //     break;
        case electronica_program:
            composer = ElectronicaComposer();
            break;
        case effects_program:
            initialize_effects();
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


