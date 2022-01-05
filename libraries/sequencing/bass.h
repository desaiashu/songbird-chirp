#ifndef SEQUENCING_BASS
#define SEQUENCING_BASS

#include "../composition/composer.h"

class BassSequencer : public Sequencer {
    private:
    public:
        BassSequencer(Scale scale=Scale(), int channel=0);
};

#endif // SEQUENCING_BASS