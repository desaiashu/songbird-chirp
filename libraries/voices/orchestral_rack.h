#ifndef VOICES_ORCHESTRAL_RACK
#define VOICES_ORCHESTRAL_RACK

#include "drum_machine.h"

class OrchestralRack : public DrumMachine {

    public:
        OrchestralRack(int midi_channel=0);
};

#endif // VOICES_ORCHESTRAL_RACK