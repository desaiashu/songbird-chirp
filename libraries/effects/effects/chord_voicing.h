#ifndef EFFECT_CHORD_VOICING
#define EFFECT_CHORD_VOICING

#ifdef ARDUINO
#include <effect.h>
#else
#include "../effect.h"
#endif

class ChordVoicing : public Effect {
    private:
        void handle_note(int note, int velocity, bool on);
    public:
        ChordVoicing(int channel=0, Scale scale=Scale());
        Scale scale;
        void note_on(int note, int velocity) override;
        void note_off(int note, int velocity) override;
};

#endif // EFFECT_CHORD_VOICING