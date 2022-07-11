#ifndef MODULATOR
#define MODULATOR

enum mod_type {
    NO_MOD,
    SIN_WAVE,
    TRI_WAVE,
    // FALLING,
    // RISING,
    // SIDE_CHAIN,
    //slow rise
    //up down
    //random
    //tbd
};

struct Modulator {

        mod_type type;
        int cycle_length;
        double max_mod;
        bool step_based;
    
        Modulator(mod_type type=NO_MOD, int cycle_length=0, double max_mod=0.2, bool step_based=false);
        int mod_for_step(int step);
        int mod_for_tick(int tick);
};

#endif // MODULATOR