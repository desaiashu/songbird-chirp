#ifndef SEQUENCING_MELODY
#define SEQUENCING_MELODY

#include "../composition/composer.h"

#ifdef ARDUINO
#include <instrument.h>
#else
#include "../voices/instrument.h"
#endif

class MelodicSequencer : public Sequencer {
    private:
        int note;
        int step;
        int pattern_index;
        const int* pattern;
        int get_last_note();
        int get_next_note();
        Progression progression;
    public:
        MelodicSequencer(Progression progression, int channel=0);
        void pulse() override;
        void stop() override;
};

#endif // SEQUENCING_MELODY
