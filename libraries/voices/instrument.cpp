// #high level definition of an instrument which serves as a "voice" for the composition
#include "instrument.h"

#ifdef ARDUINO
#include <midi_io.h>
#else
#include "../interface/midi_io.h"
#endif // DEBUG

Instrument::Instrument(int midi_channel) :
    midi_channel(midi_channel)
{
    
}

void Instrument::start_note(int note, int velocity) 
{
    send_midi_note(true, note, velocity, midi_channel);
}

void Instrument::end_note(int note) 
{
    send_midi_note(false, note, 0, midi_channel);
}

void Instrument::send_note(Note note) 
{
    send_midi_note(note, midi_channel);
}

// from .midi.midi_inst import Midi_instrument

// class Instrument:
//     def __init__(
//         self,
//         midi_channel=1
//     ):
//         self.midi_inst = Midi_instrument(midi_channel)

//     def start_note(self, note, velocity):
//         self.midi_inst.start_note(note, velocity)

//     def end_note(self, note):
//         self.midi_inst.end_note(note)