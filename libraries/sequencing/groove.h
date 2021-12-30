#ifndef SEQUENCING_GROOVE
#define SEQUENCING_GROOVE

#include "../composition/composer.h"

class GrooveSequencer : public Sequencer {
    private:
    public:
        GrooveSequencer(Scale scale=Scale(), int channel=0);
};

#endif // SEQUENCING_GROOVE