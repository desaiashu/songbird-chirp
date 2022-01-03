#include "sequencer.h"

#if ARDUINO
#include <console.h>
#else
#include "../interface/console.h"
#endif

Sequencer::Sequencer(Progression progression, int channel) :
    progression(progression), scale(progression.scale)
{
    instrument = Instrument(channel);
}

void Sequencer::change_scale(Scale new_scale) 
{
    scale = new_scale;
}

void Sequencer::pulse() 
{
    println_to_console("Failed to override");
}

void Sequencer::tick() 
{
    
}

void Sequencer::start() 
{
    
}

void Sequencer::stop() 
{
    
}

// import random
// from songbird.theory.scale import Scale
// from .patterns import e_pattern

// class Sequencer:
//     def __init__(
//         self,
//         scale=Scale(),
//         pattern=e_pattern
//     ):
//         self.scale = scale
//         self.root = scale.root
//         self.note = self.root

//     def change_scale(self, scale):
//         self.scale = scale
//         self.root = scale.root
//         self.note  = self.root

//     def pulse(self):
//         pass

//     def tick(self):
//         pass

//     def start(self):
//         pass

//     def stop(self):
//         pass