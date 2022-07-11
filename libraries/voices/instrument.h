#ifndef VOICES_INSTRUMENT
#define VOICES_INSTRUMENT

#ifdef ARDUINO
#include <note.h>
#else
#include "../sequencing/note.h"
#endif

class Instrument {
    private:
    
    public:
    
        Instrument(int midi_channel=0);
        int midi_channel;
        void start_note(int note, int velocity);
        void end_note(int note);
        void send_note(Note note);
};

// #include "drum_machine.h"

#endif // VOICES_INSTRUMENT