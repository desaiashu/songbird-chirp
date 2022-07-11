#ifndef COMPOSITION_FILE_COMPOSER
#define COMPOSITION_FILE_COMPOSER

#ifdef ARDUINO
#include <composer.h>
#else
#include "../composer.h"
#endif

class FileComposer : public Composer {
    private:
    public:
        FileComposer(Scale scale=Scale());

};

#endif // COMPOSITION_FILE_COMPOSER