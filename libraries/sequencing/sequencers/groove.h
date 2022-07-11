#ifndef SEQUENCING_GROOVE
#define SEQUENCING_GROOVE

#ifdef ARDUINO
#include <sequencer.h>
#else
#include "../sequencer.h"
#endif

#ifdef ARDUINO
#include <drum_machine.h.h>
#else
#include "../../voices/drum_machine.h"
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