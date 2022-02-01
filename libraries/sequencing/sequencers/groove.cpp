// #Groove sequencing
// #laid back, aggressive,
#include "groove.h"

GrooveSequencer::GrooveSequencer(int sequence_length, int channel) : Sequencer(sequence_length, channel)
{
    drum_machine = OrchestralRack(channel);
    instrument = drum_machine;

    gen_drum_sequence(drum_machine.bass_drum, 100, four_on_floor);
    gen_drum_sequence(drum_machine.open_hat, 70, off_beat_hat, NO_MOD, Swing(DRAG_20, dur::x, true));
    gen_drum_sequence(drum_machine.snare_drum, 60, two_four_clap, NO_MOD, Swing(STRAIGHT, dur::q, true));
    gen_drum_sequence(drum_machine.shaker, 40, sixteenth_shaker, NO_MOD, Swing(DRAG_20, dur::x));

    sort(notes.begin(), notes.end());
}



// void GrooveSequencer::tom_pattern(int note, vector<int> pattern) 
// {
//     for (size_t i = 0; i < bar_length; i++)
//     {
//         int ticks = i*TICKS_PER_BAR;
//         for (size_t j = 0; j < 4; j++) {

//             ticks += rest(duration::xx);

//             pair<Note, Note> note_pair = gen_note(note, duration::xx, 70, ticks);
//             ticks = append_note(note_pair);
//         }
//     }
// }
