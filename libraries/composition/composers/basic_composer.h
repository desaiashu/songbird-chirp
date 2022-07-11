#ifndef COMPOSITION_BASIC_COMPOSER
#define COMPOSITION_BASIC_COMPOSER

#ifdef ARDUINO
#include <composer.h>
#else
#include "../composer.h"
#endif

class BasicComposer : public Composer {
    private:
    public:
        BasicComposer(Scale scale=Scale());

};

#endif // COMPOSITION_BASIC_COMPOSER