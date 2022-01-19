#ifndef ARDUINO

#include "libraries/interface/console.h"
#include "libraries/sequencing/note.h"
#include "libraries/sequencing/clock.h"
#include "libraries/theory/scale.h"
#include "libraries/theory/chord.h"
#include "libraries/theory/progression.h"

void test_notes() {
    print_to_console(note_from_number(64));
    print_to_console(note_from_number(60));
    print_to_console(note_from_number(59));
    print_to_console(number_from_note("C", 4));
    print_to_console(number_from_note("G", 5));
}

void test_progression() {
    Progression p = Progression(Scale(), 5, true);
    for (Chord chord: p.chords) {
        println_to_console(chord.name());
        print_to_console(note_from_number(chord.bass));
        for (int i : chord.notes) {
            print_to_console(note_from_number(i));
        }
    }  
}

void test_chords() {
    
    Scale c_minor = Scale();

    // Chord chord = Chord(c_minor, 0);
    // println_to_console(chord.name());
    // for (int i : chord.notes) {
    //     print_to_console(note_from_number(i));
    // }

    // chord = Chord(c_minor, 0, 1);
    // println_to_console(chord.name());
    // for (int i : chord.notes) {
    //     print_to_console(note_from_number(i));
    // }

    // chord = Chord(c_minor, 0, 2);
    // println_to_console(chord.name());
    // for (int i : chord.notes) {
    //     print_to_console(note_from_number(i));
    // }

    Chord chord = Chord(c_minor, 5, 0, true);
    println_to_console(chord.name());
    print_to_console(note_from_number(chord.bass));
    for (int i : chord.notes) {
        print_to_console(note_from_number(i));
    }

    chord = Chord(chord, 3, true);
    println_to_console(chord.name());
    print_to_console(note_from_number(chord.bass));
    for (int i : chord.notes) {
        print_to_console(note_from_number(i));
    }

    chord = Chord(chord, 4, true, true);
    println_to_console(chord.name());
    print_to_console(note_from_number(chord.bass));
    for (int i : chord.notes) {
        print_to_console(note_from_number(i));
    }

    chord = Chord(chord, 0, true);
    println_to_console(chord.name());
    print_to_console(note_from_number(chord.bass));
    for (int i : chord.notes) {
        print_to_console(note_from_number(i));
    }

    // print_to_console(note_from_number(64));
    // print_to_console(note_from_number(60));
    // print_to_console(note_from_number(59));
    // print_to_console(number_from_note("C", 4));
    // print_to_console(number_from_note("G", 5));
}

void test_transport() {
    Transport* transport = new Transport();
}

void test_scale() {
    Scale c_minor = Scale();
    Scale g_minor = Scale("G", 4, "minor");
    Scale c_minor_wide = Scale("C", 4, "minor", "wide");
    Scale g_minor_wide = Scale("G", 4, "minor", "wide");

    println_to_console(" ");
    println_to_console("--");
    println_to_console("C minor");
    for (auto i: c_minor.notes)
        print_to_console(note_from_number(i));

    println_to_console(" ");
    println_to_console("--");
    println_to_console("C minor wide");
    for (auto i: c_minor_wide.notes)
        print_to_console(note_from_number(i));

    println_to_console(" ");
    println_to_console("--");
    println_to_console("G minor");
    for (auto i: g_minor.notes)
        print_to_console(note_from_number(i));
    
    println_to_console(" ");
    println_to_console("--");
    println_to_console("G minor wide");
    for (auto i: g_minor_wide.notes)
        print_to_console(note_from_number(i));
    println_to_console(" ");
    println_to_console("--");

}

#endif