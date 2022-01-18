#ifndef TIME_CONSTANTS
#define TIME_CONSTANTS

// PPQ = Pulses per quarter note (1 quarter note = 1 beat)
static const int PPQ = 24;
static const int MS_PER_MIN = 60000;
static const int QUARTER_NOTE_PER_WHOLE_NOTE = 4; 
static const int TICKS_PER_PULSE = 4; // Assumes 24ppq clock and 96ppq midi files
static const int TICKS_PER_WHOLE_NOTE = TICKS_PER_PULSE*PPQ*QUARTER_NOTE_PER_WHOLE_NOTE;

static const int TICKS_PER_BAR = TICKS_PER_WHOLE_NOTE; // This may change later w/ diff time signatures

#endif // TIME_CONSTANTS