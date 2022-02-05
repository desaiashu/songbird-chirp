#ifndef SEQUENCING_HARMONY
#define SEQUENCING_HARMONY

#include "sequencer.h"

class HarmonySequencer : public Sequencer {
    private:
        sequencer_style style;
    public:
        HarmonySequencer(Progression progression, int sequence_length, int channel=0, sequencer_style style=sustained);
};

#endif // SEQUENCING_HARMONY