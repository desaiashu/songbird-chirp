#include "sequencer.h"

Sequencer::Sequencer(int sequence_length, int channel) :
    instrument(Instrument(channel)), sequence_length(sequence_length)
{
    ticks = 0;
    itr = notes.begin();
}

int Sequencer::adjusted_time(int ticks) {
    int adjusted = swing.adjust(ticks);
    if (adjusted > sequence_length) // make sure adjustment doesn't push beyond tick length
        adjusted = sequence_length;
    return adjusted;
}

int Sequencer::adjusted_velocity(int velocity, int ticks, int step) 
{
    if (mod.step_based)
        return mod.mod_for_step(step)*velocity;
    else
        return mod.mod_for_tick(ticks)*velocity;
}

void Sequencer::append_note(int note, int length, int velocity, int ticks, int step) {
    pair<Note, Note> note_pair = gen_note(note, length, adjusted_velocity(velocity, ticks, step), adjusted_time(ticks));
    notes.push_back(note_pair.first);
    notes.push_back(note_pair.second);
}

/*
It generates a sequence of notes.
*/
void Sequencer::gen_sequence(int note, int velocity) 
{
    int ticks = 0;
    int step = 0;
    vector<int>::iterator pitr = pattern.begin();
    while (ticks < sequence_length) {
        /*
        It generates a note and appends it to the note list.
        */
        if (*pitr > 0) {
            append_note(note, *pitr, velocity, ticks, step);
            step++;
        }
        
        ticks += abs(*pitr);
        pitr++;
        if (pitr == pattern.end())
            pitr = pattern.begin();
    }
}

void Sequencer::gen_drum_sequence(int note, int velocity, vector<int> p, Modulator m, Swing s) 
{
    pattern = p;
    mod = m;
    swing = s;
    gen_sequence(note, velocity);
}

void Sequencer::gen_notes_sequence(vector<int> seq_notes, vector<int> velocity) 
{
    int ticks = 0;
    int step = 0;
    vector<int>::iterator pitr = pattern.begin();
    vector<int>::iterator nitr = seq_notes.begin();
    vector<int>::iterator vitr = velocity.begin();

    while (ticks < sequence_length) {
        /*
        It generates a note and appends it to the note list.
        */
        if (*pitr > 0) {
            append_note(*nitr, *pitr, *vitr, ticks, step);
            step++;
            nitr++;
            vitr++;
            if (nitr == seq_notes.end())
                nitr = seq_notes.begin();
            if (vitr == velocity.end())
                vitr = velocity.begin();
        }
        
        ticks += abs(*pitr);
        pitr++;
        if (pitr == pattern.end())
            pitr = pattern.begin();
    }

    sort(notes.begin(), notes.end());
}

void Sequencer::set_channel(int channel)
{
    instrument.midi_channel = channel;
}

void Sequencer::gen_chord_sequence(int velocity, bool bass) 
{
    int ticks = 0;
    int step = 0;
    vector<int>::iterator pitr = pattern.begin();
    vector<Chord>::iterator citr = progression.chords.begin();
    while (ticks < sequence_length) {
        /*
        It generates a note and appends it to the note list.
        */
        if (*pitr > 0) {
            if (bass) {
                append_note(citr->bass-12, *pitr, velocity, ticks, step);
            } else {
                vector<int>::iterator nitr = citr->notes.begin();
                while (nitr != citr->notes.end()) {
                    append_note(*nitr, *pitr, velocity, ticks, step);
                    nitr++;
                }
            }
            step++;  
        } else if (*pitr == 0) {
            citr++;
            if (citr == progression.chords.end())
                citr = progression.chords.begin();
        }
        
        ticks += abs(*pitr);
        pitr++;
        if (pitr == pattern.end())
            pitr = pattern.begin();
    }

    if (!bass)
        sort(notes.begin(), notes.end());
}

void Sequencer::gen_arp_sequence(int velocity) 
{
    int ticks = 0;
    int step = 0;
    vector<int>::iterator pitr = pattern.begin();
    vector<Chord>::iterator citr = progression.chords.begin();
    while (ticks < sequence_length) {
        /*
        It generates a note and appends it to the note list.
        */
        if (*pitr > 0) {
            pair<int, double> arp_note = arp.note_for_step(*citr, step);
            append_note(arp_note.first, *pitr, velocity*arp_note.second, ticks, step);
            step++;
        } else if (*pitr == 0) {
            citr++;
            if (citr == progression.chords.end())
                citr = progression.chords.begin();
        }
        
        ticks += abs(*pitr);
        pitr++;
        if (pitr == pattern.end())
            pitr = pattern.begin();
    }
}

// void Sequencer::change_scale(Scale new_scale) 
// {
//     scale = new_scale;
// }

void Sequencer::pulse() 
{
    for (size_t i = 0; i < TICKS_PER_PULSE; i++)
        tick();
}

/*
It sends the notes in the sequence to the instrument.
*/
void Sequencer::tick() 
{
    /*
    1. The first line of the while loop is a check to see if the iterator is not at the end of the vector and if the current note’s tick value is less than or equal to the current tick value.
    2. If the above condition is true, the instrument is sent the current note.
    3. The iterator is incremented to the next note.
    4. The while loop repeats until the iterator is at the end of the vector or the current note’s tick value is greater than the current tick value.
    */
    while (itr != notes.end() && itr->tick <= ticks) {
        instrument.send_note(*itr);
        itr++;
    }

    if (ticks == sequence_length) { // Handle wrapping. Need to fire notes for both tick_length and 0
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