#ifndef SEQUENCING_BASS
#define SEQUENCING_BASS

#include "../../composition/composer.h"

class BassSequencer : public Sequencer {
    private:
        sequencer_style style;
        int pulses;  
        int step;
        int progression_step;
        int pulses_per_step;
        int pulses_per_progression_step;
        int last_note;
    public:
        BassSequencer(Progression progression, int channel=0, sequencer_style style=proggy);
        void pulse() override;
        void stop() override;
};

#endif // SEQUENCING_BASS