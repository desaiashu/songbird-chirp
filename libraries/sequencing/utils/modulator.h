#ifndef MODULATOR
#define MODULATOR

struct Modulator {

        mod_type type;
        int cycle_length;
        bool step_based;
    
        Modulator(mod_type type, int cycle_length, bool step_based=false);
        int mod_for_step(int step);
        int mod_for_tick(int tick);
};

enum mod_type {
    sin_wave,
    triangle_wave,
    falling,
    rising,
    //slow rise
    //up down
    //random
    //tbd
};

#endif // MODULATOR