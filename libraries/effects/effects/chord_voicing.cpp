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
    update_display();
}

void ChordVoicing::note_on(int note, int velocity)
{
    handle_note(note, velocity, true);
}

void ChordVoicing::note_off(int note, int velocity)
{  
    handle_note(note, velocity, false);
}

void ChordVoicing::toggle_param(int param)
{
    switch (param) {
        case 1:
            increment_scale();
            break;
        case 2:
            toggle_scale_lock();
            break;
        case 3:
            toggle_chords();
            break;
        default:
            break;
    }
    update_display();
}

void ChordVoicing::handle_note(int note, int velocity, bool on)
{
    print_to_console(note);
    print_to_console(" ");
    println_to_console(on);

    // If no scale lock, just send things through (currently, chords are not active)
    if (scale_lock == NONE) {
        if (on)
            instrument.start_note(note, velocity);
        else
            instrument.end_note(note);

        return;
    }

    int note_index = note%NOTES_PER_OCTAVE;
    int octave = note/NOTES_PER_OCTAVE;
    int note_degree = scale.note_degree(note_index);

    // If scale lock and note not in scale, return without sending anything
    if (scale_lock == MUTE && note_degree < 0)
        return;

    // If snap, snap down to the closest note in scale
    while (note_degree < 0)
    {
        note_index -= 1;
        note_degree = scale.note_degree(note_index);
    }

    // If not chords, fire off single note then return
    if (!chords) {
        if (on)
            instrument.start_note(note_index + octave*NOTES_PER_OCTAVE, velocity);
        else
            instrument.end_note(note_index + octave*NOTES_PER_OCTAVE);
    } else { // If chords, generate and return the chord
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

    return;
}

void ChordVoicing::increment_scale()
{
    int new_root = (scale.root + 1) % NOTES_PER_OCTAVE;
    scale = Scale(new_root);
}

void ChordVoicing::toggle_scale_lock()
{
    switch (scale_lock) {
        case NONE:
            scale_lock = MUTE;
            break;
        case MUTE:
            scale_lock = SNAP;
            break;
        case SNAP:
            scale_lock = NONE;
            chords = false;
            break;
        default:
            break;
    }
}

void ChordVoicing::toggle_chords()
{
    chords = !chords;
    if (chords && scale_lock == NONE) {
        toggle_scale_lock();
    }
}

void ChordVoicing::update_display()
{
    //This probably needs to be abstracted to a diff class
    d.set_label_1();
    d.set_label_2();
    d.set_label_3();
}