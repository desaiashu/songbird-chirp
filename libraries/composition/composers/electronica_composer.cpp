#include "electronica_composer.h"

#if ARDUINO
#include <console.h>
#else
#include "../../interface/console.h"
#endif

ElectronicaComposer::ElectronicaComposer(Scale scale) : Composer(scale)
{
    progression = Progression(Scale(), 1.0, 4, true);

    ChordSequencer* chords = new ChordSequencer(progression, 5);
    sequencers.push_back(chords);

    BassSequencer* bass = new BassSequencer(progression, 3);
    sequencers.push_back(bass);

    midiclock->register_sequencer(chords);
    midiclock->register_sequencer(bass);

    println_to_console("Electronica initiated");
}
