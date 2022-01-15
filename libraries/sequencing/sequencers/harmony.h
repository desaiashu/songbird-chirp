#ifndef SEQUENCING_HARMONY
#define SEQUENCING_HARMONY

#include "../../composition/composer.h"

class HarmonySequencer : public Sequencer {
    private:
        sequencer_style style;
    public:
        HarmonySequencer(Progression progression, int channel=0, sequencer_style style=sustained);
};

#endif // SEQUENCING_HARMONY