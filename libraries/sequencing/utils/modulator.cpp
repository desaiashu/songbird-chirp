// #LFOs // polyrythmic patterns to modulate parameters on synths
#include "modulator.h"

Modulator::Modulator(mod_type type, int cycle_length, bool step_based) :
                    type(type), cycle_length(cycle_length), step_based(step_based)
{
    
}

int Modulator::mod_for_step(int step) 
{
    
}

int Modulator::mod_for_tick(int tick) 
{
    if (type == NO_MOD) {
        return 1;
    } else {
        return 1;
        //TODO: modulate stuff
    }
}
