#ifndef INTERFACE_MIDI
#define INTERFACE_MIDI

#include <string>

void intialize_midi();
// TODO: midi needs to take a callback for input clock

void send_midi_note(bool on, int note, int velocity, int channel);

void send_midi_cc(int cc, int value, int channel);

void send_midi_pulse();

#endif // INTERFACE_MIDI