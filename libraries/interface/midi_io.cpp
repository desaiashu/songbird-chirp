// import board
// import busio
// import adafruit_midi

// def initialize_midi():
//     # Midi code below
//     uart = busio.UART(board.TX, board.RX, baudrate=31250, timeout=0.001)  # init UART
//     midi = adafruit_midi.MIDI(
//         midi_in=uart,
//         midi_out=uart,
//         out_channel=0,
//         debug=False,
//     )
//     print("Midi output channel:", midi.out_channel + 1)
//     return midi

// midi = initialize_midi()


#include "midi_io.h"

#if ARDUINO
#include <MIDI.h>
#include <console.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial0,  MIDI);

void intialize_midi() 
{
    MIDI.begin(MIDI_CHANNEL_OMNI);
}

void send_midi_note(bool on, int note, int velocity, int channel) 
{
    if (on) {
        MIDI.sendNoteOn(note, velocity, channel);
    } else {
        MIDI.sendNoteOff(note, velocity, channel);
    }
}

void send_midi_cc(int cc, int value, int channel) 
{

}

void send_midi_pulse() 
{
    MIDI.sendClock();
}



#else // macOS


#include "../rtmidi/RtMidi.h"
#include "console.h"
#include <cstdlib>
RtMidiOut* midiout;

static const int note_on=0x90;
static const int note_off=0x80;
static const int clock_pulse=0xF8;

void intialize_midi() 
{
    print_to_console("initializing midi");
    midiout = new RtMidiOut();
    midiout->openVirtualPort();
}

void send_midi_note(bool on, int note, int velocity, int channel) 
{
    std::vector<unsigned char> message;
    if (on) {
        message.push_back(note_on+channel);
        message.push_back(note);
        message.push_back(velocity);
        midiout->sendMessage( &message );
        print_to_console("Sent note");
        println_to_console(note);
    } else {
        message.push_back(note_off+channel);
        message.push_back(note);
        message.push_back(velocity);
        midiout->sendMessage( &message );
        print_to_console("Note off");
        println_to_console(note);
    }
}

void send_midi_cc(int cc, int value, int channel) 
{
    // Control Change: 176, 7, 100 (volume)
//   message[0] = 176;
//   message[1] = 7;
//   message.push_back( 100 );
//   midiout->sendMessage( &message );
}

void send_midi_pulse() 
{
    std::vector<unsigned char> message;
    message.push_back(0xF8);
    midiout->sendMessage( &message );
}

#endif



