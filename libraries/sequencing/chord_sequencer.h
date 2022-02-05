#ifndef SEQUENCING_CHORD
#define SEQUENCING_CHORD

#include "sequencer.h"

class ChordSequencer : public Sequencer {
    private: 
    public:
        ChordSequencer(Progression p, int sequence_length, int channel=0);
};

#endif // SEQUENCING_CHORD