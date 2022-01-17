#ifndef SEQUENCING_CHORD
#define SEQUENCING_CHORD

#include "../../composition/composer.h"

class ChordSequencer : public Sequencer {
    private: 
    public:
        ChordSequencer(Progression progression, int bar_length, int channel=0);
        void chord_pattern();
};

#endif // SEQUENCING_CHORD