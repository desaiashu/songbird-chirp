// # Triads
// # Major scale chords
// # Minor scale chords (how to handle multiples?)
// # Inversion
#include "chord.h"
#include <cmath>

#ifdef ARDUINO
#include <note.h>
#else
#include "../sequencing/note.h"
#endif

vector<int> invert(int root, int third, int fifth, int seventh, int inversion) {
    vector<int> notes;
    switch (inversion) {
        case 3:
            notes.push_back(seventh);
            notes.push_back(root+NOTES_PER_OCTAVE);
            notes.push_back(third+NOTES_PER_OCTAVE);
            if (fifth > 0)
                notes.push_back(fifth+NOTES_PER_OCTAVE);
            break;
        case 2:
            if (fifth > 0)
                notes.push_back(fifth);
            if (seventh > 0)
                notes.push_back(seventh);
            notes.push_back(root+NOTES_PER_OCTAVE);
            notes.push_back(third+NOTES_PER_OCTAVE);
            break;
        case 1:
            notes.push_back(third);
            if (fifth > 0)
                notes.push_back(fifth);
            if (seventh > 0)
                notes.push_back(seventh);
            notes.push_back(root+NOTES_PER_OCTAVE);
            break;
        case 0:
            notes.push_back(root);
            notes.push_back(third);
            if (fifth > 0)
                notes.push_back(fifth);
            if (seventh > 0)
                notes.push_back(seventh);
            break;
    }
    return notes;
}

double score_voicing(vector<int> prior_notes, vector<int> new_notes, Scale scale) {

    double score = 1.0;

    // Deduct points for missing common tones
    for (int i : prior_notes) {
        for (int j : new_notes) {
            if (i % NOTES_PER_OCTAVE == j % NOTES_PER_OCTAVE) {
                if (i != j) {
                    score -= 0.3;
                }
            }
        }
    }

    // Deduct points for distance
    // Todo: deal with cases of mismatched # of notes
    size_t x = 0;
    for (int i : prior_notes) {
        int j = new_notes[x];
        score -= std::abs(scale.note_degree(i)-scale.note_degree(j))*0.05;
        x += 1;
    }

    // Deduct points for parallel fifths and octaves
    // Todo: deal with cases of mismatched # of notes
    // Todo: deal with cases where parallel octaves/fifths are wider than one octave
    for (size_t i = 0; i < prior_notes.size()-1; i++)
    {
        int prior_dist = scale.note_degree(prior_notes[i+1])-scale.note_degree(prior_notes[i]);
        int new_dist = scale.note_degree(new_notes[i+1])-scale.note_degree(new_notes[i+1]);
        if (prior_dist == new_dist && (prior_dist == FIFTH_DEGREE || prior_dist == OCTAVE_DEGREE))
            score -= 0.2;
    }

    // Deduct points if leading tone does not lead to tonic
    
    return score;
}

double score_bass(int prior_bass, int new_bass, vector<int> prior_notes, vector<int> new_notes, Scale scale) {
    double score = 1.0;
    
    // Deduct points if no contrary motion
    bool contrary_motion = false;
    int movement = 0;
    for (size_t i = 0; i < prior_notes.size()+1; i++)
    {
        int dist;
        if (i < prior_notes.size()) 
            dist = new_notes[i]-prior_notes[i];
        else
            dist = new_bass-prior_bass;

        if (dist < 1) {
            if (movement == 0)
                movement = -1;
            else if (movement > 0)
                contrary_motion = true;
        } else {
            if (movement == 0)
                movement = 1;
            else if (movement < 0)
                contrary_motion = true;
        }
    }
    if (!contrary_motion)
        score -= 0.1;

    // Deduct points for parallel fifths and octaves
    // Todo: deal with cases of mismatched # of notes
    for (size_t i = 0; i < prior_notes.size(); i++)
    {
        int prior_dist = scale.note_degree(prior_notes[i])-scale.note_degree(prior_bass);
        int new_dist = scale.note_degree(new_notes[i])-scale.note_degree(new_bass);
        if (prior_dist == new_dist && (prior_dist == FIFTH_DEGREE || prior_dist == OCTAVE_DEGREE))
            score -= 0.2;
    }

    // Deduct points if doubling leading tone
    if (new_bass == scale.notes[SEVENTH_DEGREE])
        score -= 0.4;

    return score;
}

Chord::Chord(Scale scale, int degree, int inversion, bool seventh, bool harmonic, bool fifth) :
    scale(scale), degree(degree), inversion(inversion), seventh(seventh), harmonic(harmonic), fifth(fifth)
{
    int c_root = scale.notes[degree];
    int c_third = scale.notes[(degree+THIRD_DEGREE)%7];
    if (degree+THIRD_DEGREE >= OCTAVE_DEGREE)
        c_third += NOTES_PER_OCTAVE;
    int c_fifth = scale.notes[(degree+FIFTH_DEGREE)%7];
    if (degree+FIFTH_DEGREE >= OCTAVE_DEGREE)
        c_fifth += NOTES_PER_OCTAVE;
    int c_seventh = scale.notes[(degree+SEVENTH_DEGREE)%7];
    if (degree+SEVENTH_DEGREE >= OCTAVE_DEGREE)
        c_seventh += NOTES_PER_OCTAVE;
    if (!seventh) 
        c_seventh = 0;
    if (!fifth)
        c_fifth = 0;

    if (harmonic) { // Shift to harmonic minor from minor scale
        if (seventh && degree == 1)
            c_seventh += 1;
        else if (fifth && degree == 3) // Not commonly used
            c_fifth += 1;
        else if (degree == 5)
            c_third += 1;
        else if (degree == 7)
            c_root += 1;
    }

    notes = invert(c_root, c_third, c_fifth, c_seventh, inversion);

    //Todo: allow for varied bass?
    bass = c_root-12;
}

Chord::Chord(Chord chord, int degree, bool seventh, bool harmonic) :
    scale(chord.scale), degree(degree), harmonic(harmonic), seventh(seventh)
{
    int c_root = scale.notes[degree];
    int c_third = scale.notes[(degree+THIRD_DEGREE)%7];
    if (degree+THIRD_DEGREE >= OCTAVE_DEGREE)
        c_third += NOTES_PER_OCTAVE;
    int c_fifth = scale.notes[(degree+FIFTH_DEGREE)%7];
    if (degree+FIFTH_DEGREE >= OCTAVE_DEGREE)
        c_fifth += NOTES_PER_OCTAVE;
    int c_seventh = scale.notes[(degree+SEVENTH_DEGREE)%7];
    if (degree+SEVENTH_DEGREE >= OCTAVE_DEGREE)
        c_seventh += NOTES_PER_OCTAVE;
    if (!seventh) 
        c_seventh = 0;

    if (harmonic) { // Shift to harmonic minor from minor scale
        if (seventh && degree == 1)
            c_seventh += 1;
        else if (fifth && degree == 3) // Not commonly used
            c_fifth += 1;
        else if (degree == 5)
            c_third += 1;
        else if (degree == 7)
            c_root += 1;
    }

    int closest_inversion = 0;
    double score = -100.0;
    int inversions = 2;
    if (seventh) {
        inversions = 3;
    }

    // use highest scoring inversion
    // TODO: handle wide chords. currently assumes all notes within an octave.
    for (size_t i = 0; i <= inversions; i++)
    {
        //Get inversion
        vector<int> voicing = invert(c_root, c_third, c_fifth, c_seventh, i);

        //Try voicing where root is lower than prior root
        int offset = (chord.notes[0] - voicing[0]) / NOTES_PER_OCTAVE;
        if (voicing[0] > chord.notes[0])
            offset -= 1;
        for (size_t j = 0; j < voicing.size(); j++)
        {
            voicing[j] += offset*NOTES_PER_OCTAVE;
        }
        double voicing_score = score_voicing(chord.notes, voicing, scale);
        if (voicing_score > score) {
            score = voicing_score;
            notes = voicing; //Creates copy of voicing
            inversion = i;
        }
        
        //Try voicing where c_root is higher than prior root
        for (size_t j = 0; j < voicing.size(); j++)
        {
            voicing[j] += NOTES_PER_OCTAVE;
        }
        voicing_score = score_voicing(chord.notes, voicing, scale);
        if (voicing_score > score) {
            score = voicing_score;
            notes = voicing; //Creates copy of voicing
            inversion = i;
        }

        //TODO: try losing the fifth and/or doubling root

    }

    // Todo: try various bass notes, use root or tonal degree (1/4/5 degree), prefer not using third or 7th
    bass = c_root-12;
}

string Chord::name() 
{
    return scale.name() + " degree " + std::to_string(degree) + " inversion " + std::to_string(inversion);
}