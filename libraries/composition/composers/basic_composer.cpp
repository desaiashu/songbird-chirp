#include "basic_composer.h"

#if ARDUINO
#include <console.h>
#else
#include "../../interface/console.h"
#endif

BasicComposer::BasicComposer(Scale scale) : Composer(scale)
{
    // int melody_channel = 0;
    // MelodicSequencer* melody = new MelodicSequencer(scale, melody_channel);
    // sequencers.push_back(melody);

    // println_to_console("Basic initiated");

    // midiclock->register_sequencer(melody);
}




// # a composer that only composes for one instrument and a chorus, mostly for testing

// from songbird.clock.clock import clock
// from songbird.notes.note import note_from_number, number_from_note
// from songbird.theory.circle_of_fifths import minor_fifths
// from songbird.sequencing.melody import MelodicSequencer
// from .composer import Composer
// from songbird.theory.scale import Scale
// from songbird.voices.instrument import Instrument

// class BasicComposer(Composer):
// # Scale initialization
//     def __init__(
//         self,
//         step_callback=None,
//         scale=Scale()
//     ):
//         super().__init__(scale)
//         self.sequencer = MelodicSequencer(scale)
//         self.sequencer.step_callback = step_callback
//         self.instrument = Instrument(2)
//         self.sequencer.instrument = self.instrument

//         clock.register_sequencer(self.sequencer)

//     def change_scale(self):
//         new_index = (minor_fifths.index(self.scale.root_note)+1) % len(minor_fifths)
//         new = minor_fifths[new_index]
//         self.scale = Scale(new, 4, "minor", "wide")
//         self.sequencer.change_scale(self.scale)
//         return self.scale.name()


