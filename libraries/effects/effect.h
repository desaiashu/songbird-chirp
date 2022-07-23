#ifndef EFFECTS_EFFECT
#define EFFECTS_EFFECT

#ifdef ARDUINO
#include <note.h>
#include <scale.h>
#include <instrument.h>
#include <progression.h>
#include <console.h>
#include <display.h>
#else
#include "../sequencing/note.h"
#include "../theory/scale.h"
#include "../theory/progression.h"
#include "../voices/instrument.h"
#include "../interface/console.h"
#include "../interface/display.h"
#endif

class Effect {
    public:
        Effect(int channel=0);
        virtual void note_on(int note, int velocity);
        virtual void note_off(int note, int velocity);
        virtual void toggle_param(int param);
        Instrument instrument;
        // Display& disp;
};

#ifdef ARDUINO
#include <note_cloud.h>
#include <chord_voicing.h>
#else
#include "effects/note_cloud.h"
#include "effects/chord_voicing.h"
#endif


#endif // EFFECTS_EFFECT