#include "electronica_composer.h"

ElectronicaComposer::ElectronicaComposer(Scale scale) : Composer(scale)
{
    int melody_channel = 0;
    MelodicSequencer melody(scale, melody_channel);
    sequencers.push_back(melody);

    midiclock->register_sequencer(melody);
}
