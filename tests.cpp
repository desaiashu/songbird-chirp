#ifndef ARDUINO

#include "libraries/interface/console.h"
#include "libraries/notes/note.h"
#include "libraries/clock/clock.h"
#include "libraries/theory/scale.h"

void test_notes() {
    print_to_console(note_from_number(64));
    print_to_console(note_from_number(60));
    print_to_console(note_from_number(59));
    print_to_console(number_from_note("C", 4));
    print_to_console(number_from_note("G", 5));
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