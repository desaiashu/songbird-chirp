#include "orchestral_rack.h"

OrchestralRack::OrchestralRack(int midi_channel) :
    DrumMachine(midi_channel)
{
    bass_drum = 36;

    snare_drum = 38;
    hand_clap = 0;

    open_hat = 46;
    closed_hat = 0;

    shaker = 44;
    ride_snare = 0;
    ride_cymbal = 0;
    crash_cymbal = 0;

    low_tom = 45;
    mid_tom = 40;
    high_tom = 50;

    perc_1 = 0;
    perc_2 = 0;
    perc_3 = 0;
}