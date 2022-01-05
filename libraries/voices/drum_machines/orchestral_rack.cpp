#include "orchestral_rack.h"

OrchestralRack::OrchestralRack(int midi_channel) :
    DrumMachine(midi_channel)
{
    bass_drum = 24;

    snare_drum = 26;
    hand_clap = 0;

    open_hat = 34;
    closed_hat = 0;

    shaker = 32;
    ride_snare = 0;
    ride_cymbal = 0;
    crash_cymbal = 0;

    low_tom = 33;
    mid_tom = 28;
    high_tom = 38;

    perc_1 = 0;
    perc_2 = 0;
    perc_3 = 0;
}