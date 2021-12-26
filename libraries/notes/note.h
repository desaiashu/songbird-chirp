#ifndef NOTES_NOTE
#define NOTES_NOTE

#define NOTES_PER_OCTAVE 12

#include <string> 
using std::string;

const int number_from_note(const string note, const int octave);

const string note_from_number(const int num);

#endif // NOTES_NOTE