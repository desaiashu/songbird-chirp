// # Circle of fifths progression
// # Wheel of common chord patterns
#include "progression.h"

enum chord_notation {
    i, I, iio, ii, iii, III, iv, IV, v, V, vi, VI, viio, VII
};

chord_notation get_minor_classical_triad_for_step(int step) {
    step = step % 7;
    int r;
    switch (step) {
        case 0:
            return i;
        case 1:
            r = rand()%2;
            if (r == 0)
                return V;
            return viio;
        case 2:
            r = rand()%2;
            if (r == 0)
                return iio;
            return iv;
        case 3:
            return VI;
        case 4:
            return III;
        case 5:
            return VII;
        case 6:
            return iv;
    }
}

chord_notation get_major_classical_triad_for_step(int step) {
    step = step % 7;
    int r;
    switch (step) {
        case 0:
            return I;
        case 1:
            r = rand()%2;
            if (r == 0)
                return V;
            return viio;
        case 2:
            r = rand()%2;
            if (r == 0)
                return ii;
            return IV;
        case 3:
            return vi;
        case 4:
            return iii;
        case 5:
            return viio;
        case 6:
            return IV;
    }
}

Chord chord_from_notation_and_scale(chord_notation chord, bool seventh, Scale scale, Chord last_chord, bool initial) {
    int degree;
    bool harmonic = false;

    switch (chord) {
        case i:
            degree = 0;
            break;
        case I:
            degree = 0;
            break;
        case iio:
            degree = 1;
            break;
        case ii:
            degree = 1;
            break;
        case iii:
            degree = 2;
            break;
        case III:
            degree = 2;
            break;
        case iv:
            degree = 3;
            break;
        case IV:
            degree = 3;
            break;
        case v:
            degree = 4;
            break;
        case V:
            degree = 4;
            if (scale.mode == "minor")
                harmonic = true;
            break;
        case vi:
            degree = 5;
            break;
        case VI:
            degree = 5;
            break;
        case viio:
            degree = 6;
            if (scale.mode == "minor")
                harmonic = true;
            break;
        case VII:
            degree = 6;
            break;
    }

    if (initial)
        return Chord(scale, degree, 0, seventh, harmonic);
    else
        return Chord(last_chord, degree, seventh, harmonic);
}

Progression::Progression(Scale scale, int length, bool seventh) {
    Chord chord = Chord();
    bool initial = true;
    while (length > 0) {
        chord_notation n = get_minor_classical_triad_for_step(length-1);
        chord = chord_from_notation_and_scale(n, seventh, scale, chord, initial);
        chords.push_back(chord);
        initial = false;
        length -= 1;
    }
}