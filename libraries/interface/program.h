#ifndef INTERFACE_PROGRAM
#define INTERFACE_PROGRAM

#ifdef ARDUINO
#include <composer.h>
#else
#include "../composition/composer.h"
#endif

class Program {
    private:
        int program_index;

    Composer composer;

    public:
        Program(int program_index);
};

#endif // INTERFACE_PROGRAM