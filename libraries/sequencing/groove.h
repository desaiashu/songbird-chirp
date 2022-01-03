#ifndef SEQUENCING_GROOVE
#define SEQUENCING_GROOVE

#include "../composition/composer.h"

class GrooveSequencer : public Sequencer {
    private:
    public:
        GrooveSequencer(Progression progression, int channel=0);
};

#endif // SEQUENCING_GROOVE