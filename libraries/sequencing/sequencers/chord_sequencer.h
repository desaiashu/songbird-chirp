#ifndef SEQUENCING_CHORD
#define SEQUENCING_CHORD

#include "../../composition/composer.h"

class ChordSequencer : public Sequencer {
    private: 
        int pulses;  
        int step;
        int pulses_per_step;
    public:
        ChordSequencer(Progression progression, int channel=0);
        void pulse() override;
        void stop() override;
};

#endif // SEQUENCING_CHORD