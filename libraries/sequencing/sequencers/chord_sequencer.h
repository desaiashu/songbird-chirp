#ifndef SEQUENCING_CHORD
#define SEQUENCING_CHORD

#ifdef ARDUINO
#include <sequencer.h>
#else
#include "../sequencer.h"
#endif

class ChordSequencer : public Sequencer {
    private: 
    public:
        ChordSequencer(Progression p, int sequence_length, int channel=0);
};

#endif // SEQUENCING_CHORD