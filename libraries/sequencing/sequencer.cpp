#include "sequencer.h"

Sequencer::Sequencer(Scale scale, int channel) :
    scale(scale), channel(channel)
{
    
}

void Sequencer::pulse() 
{
    
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

void Sequencer::change_scale(Scale new_scale) 
{
    scale = new_scale;
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