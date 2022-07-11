// # Midi for chord voicing in response to melody
// # Can be layered on generative or midi in
#include "chord_voicing.h"

#ifdef ARDUNIO
#include <chord.h>
#include <note.h>
#else
#include "../../theory/chord.h"
#include "../../sequencing/note.h"
#endif

ChordVoicing::ChordVoicing(int channel, Scale scale) : Effect(channel), scale(scale)
{
    
}

void ChordVoicing::note_on(int note, int velocity)
{
    handle_note(note, velocity, true);
}

void ChordVoicing::note_off(int note, int velocity)
{  
    handle_note(note, velocity, false);
}

void ChordVoicing::handle_note(int note, int velocity, bool on)
{
    print_to_console(note);
    print_to_console(" ");
    println_to_console(on);
    int note_index = note%NOTES_PER_OCTAVE;
    int note_degree = scale.note_degree(note_index);
    if (note_degree >= 0) {
        int octave = note/NOTES_PER_OCTAVE;
        Chord chord = Chord(scale, note_degree);
        vector<int>::iterator nitr = chord.notes.begin();
        while (nitr != chord.notes.end()) {
            if (on)
                instrument.start_note(*nitr + octave*NOTES_PER_OCTAVE, velocity);
            else
                instrument.end_note(*nitr + octave*NOTES_PER_OCTAVE);
            print_to_console(*nitr + octave*NOTES_PER_OCTAVE);
            print_to_console(" ");
            nitr++;
        }
        println_to_console(" ");
    }

    return ;
}