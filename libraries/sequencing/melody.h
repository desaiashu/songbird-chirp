#ifndef SEQUENCING_MELODY
#define SEQUENCING_MELODY

#include "../composition/composer.h"

class MelodicSequencer : public Sequencer {
    private:
    public:
        MelodicSequencer(Scale scale=Scale(), int channel=0);
};

#endif // SEQUENCING_MELODY
