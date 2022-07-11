#ifndef COMPOSITION_LOOP_COMPOSER
#define COMPOSITION_LOOP_COMPOSER

#ifdef ARDUINO
#include <composer.h>
#else
#include "../composer.h"
#endif

class LoopComposer : public Composer {
    private:
    public:
        LoopComposer(Scale scale=Scale());

};

#endif // COMPOSITION_LOOP_COMPOSER