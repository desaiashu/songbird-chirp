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

ChordVoicing::ChordVoicing(Display* disp, int channel, Scale scale) : Effect(channel), scale(scale), display(disp)
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
            increment_instrument();
            break;
        default:
            break;
    }
    update_display();
}

void ChordVoicing::handle_note(int note, int velocity, bool on)
{
    // print_to_console(note);
    // print_to_console(" ");
    // println_to_console(on);

    //If no scale lock, just send things through (currently, chords are not active)
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

    // print_to_console(note_degree);

    // If scale lock and note not in scale, return without sending anything
    if (scale_lock == MUTE && note_degree < 0) {
        return;
        // println_to_console("muted");
    }
        

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
            // print_to_console(*nitr + octave*NOTES_PER_OCTAVE);
            // print_to_console(" ");
            nitr++;
        }
        // println_to_console(" ");  
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
    switch (setting) {
        case sNONE:
            scale_lock = MUTE;
            chords = false;
            setting = sMUTE;
            break;
        case sMUTE:
            scale_lock = SNAP;
            chords = false;
            setting = sSNAP;
            break;
        case sSNAP:
            scale_lock = MUTE;
            chords = true;
            setting = sCHORDSMUTE;
            break;
        case sCHORDSMUTE:
            scale_lock = SNAP;
            chords = true;
            setting = sCHORDSSNAP;
            break;
        case sCHORDSSNAP:
            scale_lock = NONE;
            chords = false;
            setting = sNONE;
            break;
        default:
            break;
    }
}

void ChordVoicing::increment_instrument()
{
    instrument.midi_channel += 1;
    if (instrument.midi_channel == 10) {
        instrument.midi_channel = 6;
    }
}

// void ChordVoicing::toggle_chords()
// {
//     chords = !chords;
//     if (chords && scale_lock == NONE) {
//         toggle_scale_lock();
//     }
// }

void ChordVoicing::update_display()
{
    #ifdef ARDUINO

    //This probably needs to be abstracted to a diff class

    display->set_label(1, "Scale: " + note_from_number(scale.root) + " min");

    string lock = "Lock: ";
    switch (scale_lock) {
        case NONE:
            lock += "off";
            break;
        case MUTE:
            lock += "mute";
            break;
        case SNAP:
            lock += "snap";
            break;
        default:
            lock += "error";
            break;
    }
    if (chords)
        lock += " + chords";

    display->set_label(2, lock);

    display->set_label(3, "Channel: " + std::to_string(instrument.midi_channel));

    #endif // DEBUG

}