#ifndef EFFECTS_MIDI_EFFECTS
#define EFFECTS_MIDI_EFFECTS

// #include "time_constants.h"
#include "effect.h"

#include <thread>
#include <vector>
using std::vector;

class MIDIEffects {
    public:
        static MIDIEffects& getInstance()
        {
            static MIDIEffects instance;
            return instance;
        }

        vector<Effect*> effects;
        void register_effect(Effect* effect);

        void note_on(int note, int vel, int channel);
        void note_off(int note, int vel, int channel);
        void toggle_param(int param);
};


#ifndef MIDI_EFFECTS
#define MIDI_EFFECTS
static MIDIEffects* midieffects = &MIDIEffects::getInstance();
#endif // !MIDI_EFFECTS


#endif // EFFECTS_MIDI_EFFECTS