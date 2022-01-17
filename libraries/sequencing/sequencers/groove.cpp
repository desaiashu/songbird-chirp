// #Groove sequencing
// #laid back, aggressive,
#include "groove.h"

GrooveSequencer::GrooveSequencer(Progression progression, int bar_length, int channel) : Sequencer(progression, bar_length, channel)
{
    drum_machine = OrchestralRack(channel);
    instrument = drum_machine;

    kick_pattern(drum_machine.bass_drum);
    hh_pattern(drum_machine.open_hat);
    clap_pattern(drum_machine.snare_drum);
    shaker_pattern(drum_machine.shaker);

    sort(notes.begin(), notes.end());
}

void GrooveSequencer::kick_pattern(int note) 
{
    for (size_t i = 0; i < bar_length; i++)
    {
        int ticks = i*TICKS_PER_BAR;
        for (size_t j = 0; j < 4; j++) {

            pair<Note, Note> note_pair = eighth_note(note, 127, ticks);
            ticks = append_note(note_pair);
            
            ticks += eighth_rest();
        }
    }
}

void GrooveSequencer::tom_pattern(int note) 
{
    
}

void GrooveSequencer::hh_pattern(int note) 
{
    for (size_t i = 0; i < bar_length; i++)
    {
        int ticks = i*TICKS_PER_BAR;
        for (size_t j = 0; j < 4; j++) {

            ticks += eighth_rest();

            pair<Note, Note> note_pair = eighth_note(note, 100, ticks);
            ticks = append_note(note_pair);
        }
    }
}

void GrooveSequencer::clap_pattern(int note) 
{
    for (size_t i = 0; i < bar_length; i++)
    {
        int ticks = i*TICKS_PER_BAR;
        for (size_t j = 0; j < 2; j++) {

            ticks += quarter_rest();

            pair<Note, Note> note_pair = eighth_note(note, 100, ticks);
            ticks = append_note(note_pair);
        }
    }
}

void GrooveSequencer::shaker_pattern(int note) 
{
    for (size_t i = 0; i < bar_length; i++)
    {
        int ticks = i*TICKS_PER_BAR;
        for (size_t j = 0; j < 16; j++) {
            pair<Note, Note> note_pair = sixteenth_note(note, 50, ticks);
            ticks = append_note(note_pair);
        }
    }
}

