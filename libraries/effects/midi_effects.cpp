// #acts as master clock
// #takes in midi clock if it's sensing one, otherwise sets BPM internally
// #registers instruments to master clock

#include "midi_effects.h"
#if ARDUINO
#include <console.h>
#include <midi_io.h>
#else
#include "../interface/console.h"
#include "../interface/midi_io.h"
#include <unistd.h>
#endif

// MIDIEffects::MIDIEffects()
// {
    
// }

void MIDIEffects::register_effect(Effect* effect) 
{
    effects.push_back(effect);
}


void MIDIEffects::note_on(int note, int vel, int channel)
{
    for (Effect* e : effects)
        if (e->instrument.midi_channel == channel)
            e->note_on(note, vel);     
}

void MIDIEffects::note_off(int note, int vel, int channel)
{
    for (Effect* e : effects)
        if (e->instrument.midi_channel == channel)
            e->note_off(note, vel);
}

void MIDIEffects::toggle_param(int param)
{
    //TODO: test if effect or effect menu is active
    for (Effect* e : effects)
        e->toggle_param(param); 
}
