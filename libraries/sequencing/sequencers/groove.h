#ifndef SEQUENCING_GROOVE
#define SEQUENCING_GROOVE

#include "../../composition/composer.h"

#ifdef ARDUINO
#include <drum_machine.h>
#else
#include "../../voices/drum_machines/drum_machine.h"
#endif

class GrooveSequencer : public Sequencer {
    private:
        DrumMachine drum_machine;
    public:
        GrooveSequencer(Progression progression, int bar_length=4, int channel=0);
        
        // void kick_pattern(int note, vector<int> pattern);
        // void tom_pattern(int note, vector<int> pattern);
        // void hh_pattern(int note, vector<int> pattern);
        // void clap_pattern(int note, vector<int> pattern);
        // void shaker_pattern(int note, vector<int> pattern);
};

#endif // SEQUENCING_GROOVE