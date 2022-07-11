// # Midi for chord voicing in response to melody
// # Can be layered on generative or midi in
#include "chord_voicing.h"

ChordVoicing::ChordVoicing(int channel) : Effect(channel)
{
    
}

void ChordVoicing::note_on(int note, int velocity)
{
    println_to_console("chord voice note on");
    instrument.start_note(note+3, velocity);
    instrument.start_note(note+7, velocity);
}

void ChordVoicing::note_off(int note, int velocity)
{
    println_to_console("chord voice note off");
    instrument.end_note(note+3);
    instrument.end_note(note+7);
}

