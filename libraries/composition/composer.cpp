#include "composer.h"

Composer::Composer(Scale scale) :
    scale(scale)
{
    
}

void Composer::change_scale(Scale new_scale) 
{
    for (Sequencer s : sequencers) {
        s.change_scale(new_scale);
    }
}

// from songbird.theory.scale import Scale

// class Composer:
//     def __init__(
//         self,
//         scale=Scale(),
//     ):
//         self.scale = scale