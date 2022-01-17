#ifndef VOICES_INSTRUMENT
#define VOICES_INSTRUMENT

#ifdef ARDUINO
#include <utils.h>
#else
#include "../sequencing/utils/note.h"
#endif

class Instrument {
    private:
        int midi_channel;

    public:
        Instrument(int midi_channel=0);
        void start_note(int note, int velocity);
        void end_note(int note);
        void send_note(Note note);
};

#endif // VOICES_INSTRUMENT