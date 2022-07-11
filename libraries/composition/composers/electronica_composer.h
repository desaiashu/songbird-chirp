#ifndef COMPOSITION_ELECTRONICA_COMPOSER
#define COMPOSITION_ELECTRONICA_COMPOSER

#ifdef ARDUINO
#include <composer.h>
#else
#include "../composer.h"
#endif

class ElectronicaComposer : public Composer {
    private:
        Progression progression;
    public:
        ElectronicaComposer(Scale scale=Scale());

};

#endif // COMPOSITION_BASIC_COMPOSER