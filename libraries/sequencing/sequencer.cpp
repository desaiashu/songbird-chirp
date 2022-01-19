#include "sequencer.h"

Sequencer::Sequencer(Progression progression, int bar_length, int channel) :
    progression(progression), scale(progression.scale), bar_length(bar_length), tick_length(bar_length*TICKS_PER_BAR)
{
    instrument = Instrument(channel);
    ticks = 0;
    itr = notes.begin();
}

int Sequencer::adjusted(int ticks, Swing swing) {
    int adjusted = swing.adjust(ticks);
    if (adjusted > tick_length) // make sure adjustment doesn't push beyond tick length
        adjusted = tick_length;
    return adjusted;
}

void Sequencer::gen_sequence(int note, int velocity, vector<int> pattern, Swing swing) 
{
    int ticks = 0;
    vector<int>::iterator pitr = pattern.begin();
    while (ticks < tick_length) {
        if (*pitr > 0) {
            pair<Note, Note> note_pair = gen_note(note, *pitr, 70, adjusted(ticks, swing));
            append_note(note_pair);   
        }
        
        ticks += abs(*pitr);
        pitr++;
        if (pitr == pattern.end())
            pitr = pattern.begin();
    }
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

    if (ticks == tick_length) { // Handle wrapping. Need to fire notes for both tick_length and 0
        ticks = 0;
        itr = notes.begin(); //reset to start of sequence
        while (itr != notes.end() && itr->tick <= ticks) {
            instrument.send_note(*itr);
            itr++;
        }
    }
    
    ticks++;
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