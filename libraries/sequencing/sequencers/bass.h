#ifndef SEQUENCING_BASS
#define SEQUENCING_BASS

#include "../../composition/composer.h"

class BassSequencer : public Sequencer {
    private:
        sequencer_style style;
    public:
        BassSequencer(Progression progression, int bar_length, int channel=0, sequencer_style style=proggy);
        void bass_pattern();
};

#endif // SEQUENCING_BASS