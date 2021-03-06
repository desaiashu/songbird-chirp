#ifndef VOICES_DRUM_MACHINE
#define VOICES_DRUM_MACHINE

#include "instrument.h"

class DrumMachine : public Instrument {

    public:
        int bass_drum;

        int snare_drum;
        int hand_clap;

        int open_hat;
        int closed_hat;

        int shaker;
        int ride_snare;
        int ride_cymbal;
        int crash_cymbal;

        int low_tom;
        int mid_tom;
        int high_tom;

        int perc_1;
        int perc_2;
        int perc_3;

        DrumMachine(int midi_channel=0);
};

#ifdef ARDUINO
#include <orchestral_rack.h>
// #include <ableton_drum_rack.h>
// #include <nord_drum.h>
// #include <tr8s.h>
#else
#include "drum_machines/orchestral_rack.h"
// #include "drum_machines/ableton_drum_rack.h"
// #include "drum_machines/nord_drum.h"
// #include "drum_machines/tr8s.h"
#endif


#endif // VOICES_DRUM_MACHINE