#ifndef COMPOSITION_COMPOSER
#define COMPOSITION_COMPOSER

#ifdef ARDUINO
#include <scale.h>
#include <sequencer.h>
#include <instrument.h>
#include <clock.h>
#else
#include "../theory/scale.h"
#include "../sequencing/sequencer.h"
#include "../voices/instrument.h"
#include "../sequencing/clock.h"
#endif

#include <vector>
using std::vector;

class Composer {
    protected:
        vector<Sequencer*> sequencers;
    public:
        Scale scale;
        Composer(Scale scale=Scale());
        void change_scale(Scale new_scale);
};

// Includes for convenience of other classes
#include "../composition/composers/basic_composer.h"
#include "../composition/composers/file_composer.h"
#include "../composition/composers/loop_composer.h"
#include "../composition/composers/electronica_composer.h"

#endif // COMPOSITION_COMPOSER