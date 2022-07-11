#ifndef VOICES_ORCHESTRAL_RACK
#define VOICES_ORCHESTRAL_RACK

#ifdef ARDUINO
#include <drum_machine.h>
#else
#include "../drum_machine.h"
#endif

class OrchestralRack : public DrumMachine {

    public:
        OrchestralRack(int midi_channel=0);
};

#endif // VOICES_ORCHESTRAL_RACK