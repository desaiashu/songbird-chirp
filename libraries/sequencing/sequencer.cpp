#include "sequencer.h"

Sequencer::Sequencer(Progression progression, int bar_length, int channel) :
    progression(progression), scale(progression.scale), bar_length(bar_length), tick_length(bar_length*TICKS_PER_BAR)
{
    instrument = Instrument(channel);
    ticks = 0;
    itr = notes.begin();
}

/*
1. The adjusted() function takes a tick value and a Swing object.
2. The swing object is used to adjust the tick value.
3. The adjusted value is then checked to make sure it doesn’t exceed the tick length.
4. If it does, the adjusted value is set to the tick length.
5. The adjusted value is then returned.
*/
int Sequencer::adjusted(int ticks, Swing swing) {
    int adjusted = swing.adjust(ticks);
    if (adjusted > tick_length) // make sure adjustment doesn't push beyond tick length
        adjusted = tick_length;
    return adjusted;
}

/*
It generates a sequence of notes.
*/
void Sequencer::gen_sequence(int note, int velocity, vector<int> pattern, Swing swing) 
{
    int ticks = 0;
    vector<int>::iterator pitr = pattern.begin();
    while (ticks < tick_length) {
        /*
        It generates a note and appends it to the note list.
        */
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

void Sequencer::gen_chord_sequence(Progression progression, int velocity, vector<int> pattern, Swing swing, bool bass) 
{
    int ticks = 0;
    vector<int>::iterator pitr = pattern.begin();
    vector<Chord>::iterator citr = progression.chords.begin();
    while (ticks < tick_length) {
        /*
        It generates a note and appends it to the note list.
        */
        if (*pitr > 0) {
            if (bass) {
                pair<Note, Note> note_pair = gen_note(citr->bass, *pitr, 70, adjusted(ticks, swing));
                append_note(note_pair);
            } else {
                vector<int>::iterator nitr = citr->notes.begin();
                while (nitr != citr->notes.end()) {
                    pair<Note, Note> note_pair = gen_note(*nitr, *pitr, 70, adjusted(ticks, swing));
                    append_note(note_pair);
                    nitr++;
                }
            }
               
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

/*
1. The append_note function takes a pair of notes and adds them to the vector of notes.
2. The first note is added to the vector of notes.
3. The second note is added to the vector of notes.
4. The second note’s tick value is returned.
*/
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