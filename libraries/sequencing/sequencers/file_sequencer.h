#ifndef SEQUENCING_FILE
#define SEQUENCING_FILE

#include "../../composition/composer.h"

class FileSequencer : public Sequencer {
    private:
    public:
        FileSequencer(int channel=0);
};

#endif // SEQUENCING_FILE