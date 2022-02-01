#include "electronica_composer.h"

#if ARDUINO
#include <console.h>
#else
#include "../../interface/console.h"
#endif

ElectronicaComposer::ElectronicaComposer(Scale scale) : Composer(scale)
{
    progression = Progression(Scale(), 8, true);

    ChordSequencer* chords = new ChordSequencer(progression, 8*dur::w, 5);
    sequencers.push_back(chords);

    BassSequencer* bass = new BassSequencer(progression, 8*dur::w, 3);
    sequencers.push_back(bass);

    GrooveSequencer* drums = new GrooveSequencer(4*dur::w, 1);
    sequencers.push_back(drums);

    midiclock->register_sequencer(chords);
    midiclock->register_sequencer(bass);
    midiclock->register_sequencer(drums);

    println_to_console("Electronica initiated");
}
