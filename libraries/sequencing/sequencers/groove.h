#ifndef SEQUENCING_GROOVE
#define SEQUENCING_GROOVE

#include "sequencer.h"

#ifdef ARDUINO
#include <instrument.h>
#else
#include "../../voices/drum_machines/drum_machine.h"
#endif

class GrooveSequencer : public Sequencer {
    private:
        DrumMachine drum_machine;
    public:
        GrooveSequencer(int sequence_length, int channel=0);
        
        // void kick_pattern(int note, vector<int> pattern);
        // void tom_pattern(int note, vector<int> pattern);
        // void hh_pattern(int note, vector<int> pattern);
        // void clap_pattern(int note, vector<int> pattern);
        // void shaker_pattern(int note, vector<int> pattern);
};

#endif // SEQUENCING_GROOVE