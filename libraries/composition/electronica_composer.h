#ifndef COMPOSITION_ELECTRONICA_COMPOSER
#define COMPOSITION_ELECTRONICA_COMPOSER

#include "composer.h"

class ElectronicaComposer : public Composer {
    private:
        Progression progression;
    public:
        ElectronicaComposer(Scale scale=Scale());

};

#endif // COMPOSITION_BASIC_COMPOSER