#include "sequencer.h"

Sequencer::Sequencer(Progression progression, int bar_length, int channel) :
    progression(progression), scale(progression.scale), bar_length(bar_length), tick_length(bar_length*TICKS_PER_BAR)
{
    instrument = Instrument(channel);
    ticks = 0;
    itr = notes.begin();
}

int Sequencer::append_note(pair<Note, Note> note_pair) {
    notes.push_back(note_pair.first);
    notes.push_back(note_pair.second);
    return note_pair.second.tick;
}

void Sequencer::change_scale(Scale new_scale) 
{
    scale = new_scale;
}

void Sequencer::pulse() 
{
    for (size_t i = 0; i < TICKS_PER_PULSE; i++)
        tick();
}

void Sequencer::tick() 
{
    while (itr != notes.end() && itr->tick <= ticks) {
        instrument.send_note(*itr);
        itr++;
    }
    
    ticks++;
    if (ticks == tick_length) {
        ticks = 0;
        itr = notes.begin(); //reset to start of sequence
    }
        
}


void Sequencer::start() 
{
    ticks = 0;
    itr = notes.begin();
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