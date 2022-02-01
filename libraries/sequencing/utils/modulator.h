#ifndef MODULATOR
#define MODULATOR

enum mod_type {
    NO_MOD,
    SIN_WAVE,
    TRI_WAVE,
    FALLING,
    RISING,
    //slow rise
    //up down
    //random
    //tbd
};

struct Modulator {

        mod_type type;
        int cycle_length;
        bool step_based;
    
        Modulator(mod_type type=NO_MOD, int cycle_length=0, bool step_based=false);
        int mod_for_step(int step);
        int mod_for_tick(int tick);
};

#endif // MODULATOR