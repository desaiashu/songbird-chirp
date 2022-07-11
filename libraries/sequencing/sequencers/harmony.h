#ifndef SEQUENCING_HARMONY
#define SEQUENCING_HARMONY

#ifdef ARDUINO
#include <sequencer.h>
#else
#include "../sequencer.h"
#endif

class HarmonySequencer : public Sequencer {
    private:
        sequencer_style style;
    public:
        HarmonySequencer(Progression p, int sequence_length, int channel=0, sequencer_style style=sustained);
};

#endif // SEQUENCING_HARMONY