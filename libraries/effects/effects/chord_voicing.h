#ifndef EFFECT_CHORD_VOICING
#define EFFECT_CHORD_VOICING

//Rename effect

#ifdef ARDUINO
#include <effect.h>
#include <display.h>
#else
#include "../effect.h"
#include "../../interface/display.h"
#endif

enum scale_lock {
        NONE,
        MUTE,
        SNAP,
        CHORDSMUTE,
        CHORDSSNAP,
};

class ChordVoicing : public Effect {
    private:
        void handle_note(int note, int velocity, bool on);
        void increment_scale();
        void toggle_scale_lock();
        void increment_instrument();

        void update_display();

        //TODO: handle major and other scales

        bool chords = false;
        int scale_lock = NONE;

    public:
        ChordVoicing(int channel=0, Scale scale=Scale("C", -1));
        Scale scale;
        void note_on(int note, int velocity) override;
        void note_off(int note, int velocity) override;
        void toggle_param(int param) override;
        
};

#endif // EFFECT_CHORD_VOICING