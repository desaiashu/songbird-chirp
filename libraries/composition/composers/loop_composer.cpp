// # a composer that composes a 32 bar loop of multiple instruments, mostly for testing
#include "loop_composer.h"

LoopComposer::LoopComposer(Scale scale) : Composer(scale)
{
    int melody_channel = 0;
    MelodicSequencer melody(scale, melody_channel);
    sequencers.push_back(melody);

    midiclock->register_sequencer(melody);
}