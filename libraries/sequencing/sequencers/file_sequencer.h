#ifndef SEQUENCING_FILE
#define SEQUENCING_FILE

#ifdef ARDUINO
#include <sequencer.h>
#else
#include "../sequencer.h"
#endif

class FileSequencer : public Sequencer {
    private:
    public:
        FileSequencer(int channel=0);
};

#endif // SEQUENCING_FILE