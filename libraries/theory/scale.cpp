// from songbird.notes.note import number_from_note, note_from_number

// # scale structures
// base_scale = [2,2,1,2,2,2,1]
// dissonants = [1, 5]
// dissonants_wide_scale = [5, 9]
// wide_scale_root = 4
#include "scale.h"
#include <map>
using std::map;
#include <list>

#ifdef ARDUINO
#include <note.h>
#else
#include "../notes/note.h"
#endif

const int base_scale_size = 7;
const int base_dissonants_size = 7;
const int base_scale[base_scale_size] = {2,2,1,2,2,2,1};
const int third = 2;
const int fifth = 4;
const int base_dissonants[2] = {1, 5};
const int base_dissonants_wide[2] = {5, 9};
const int wide_scale_root = 4;
const map<string, int> root_offset = { 
    { "major", 0 }, 
    { "dorian", 1 }, 
    { "phrygian", 2 }, 
    { "lydian", 3 }, 
    { "mixolydian", 4 }, 
    { "minor", 5 }, 
    { "locrian", 6 } 
};

Scale::Scale(string root_note, int octave, string mode, string type) 
    : root_note(root_note), octave(octave), mode(mode), type(type)
{
        root = number_from_note(root_note, octave);
        offset = root_offset.at(mode);
        if (type == "wide") {
            gen_wide_scale();
        } else {
            gen_scale();
        }
}

string Scale::name() 
{
    return root_note + " " + mode;
}

void Scale::gen_scale(bool base) 
{
    notes.push_back(root);
    int distance = 0;
    for (size_t i = 0; i < base_scale_size; i++)
    {
        distance += base_scale[(i+offset) % 7];
        notes.push_back(root+distance);
    }
    if (base)
        for (size_t i = 0; i < base_dissonants_size; i++)
            dissonants.push_back(base_dissonants[i]);
}

void Scale::gen_wide_scale() 
{
    gen_scale(false);
    int lower_root = root-NOTES_PER_OCTAVE;
    int lower_third_distance = notes[third]-root;
    int lower_fifth_distance = notes[fifth]-root;
    notes.insert(notes.begin(), { lower_root-NOTES_PER_OCTAVE, lower_root, lower_root+lower_third_distance, lower_root+lower_fifth_distance });
    for (size_t i = 0; i < base_dissonants_size; i++)
        dissonants.push_back(base_dissonants_wide[i]);
}
