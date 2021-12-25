#ifndef ARDUINO

#include "libraries/interface/console.h"
#include "libraries/notes/note.h"

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

#endif