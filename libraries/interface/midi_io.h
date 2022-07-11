#ifndef INTERFACE_MIDI
#define INTERFACE_MIDI

#include <string>

#ifdef ARDUINO
#include <note.h>
#else
#include "../sequencing/note.h"
#endif

void intialize_midi();
// TODO: midi needs to take a callback for input clock

void read_midi();

void send_midi_note(bool on, int note, int velocity, int channel);
inline void send_midi_note(Note note, int channel) { send_midi_note(note.on, note.note, note.velocity, channel); };

void send_midi_cc(int cc, int value, int channel);

void send_midi_pulse();

#endif // INTERFACE_MIDI