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
#include <clock.h>
#include <thread>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial0,  MIDI);
std::thread midi_thread;

// Midi input handlers
void midi_loop()
{
    while (true) {  
        MIDI.read();
    }
}

void handle_note_off(byte channel, byte note, byte velocity){
    //Send to effects
}
void handle_note_on(byte channel, byte note, byte velocity){
    //Send to effects
}

void handleSongPosition(unsigned int beats){

}

void handle_clock(void){
    //Send to clock if clock internal
     if (!midiclock->internal) {
        midiclock->pulse();
     }
}

void handle_start(void){
    if (!midiclock->internal)
        midiclock->start();
}

void handle_continue(void){
    //Send to clock if clock internal
}

void handle_stop(void){
    //Send to clock if clock internal
    if (!midiclock->internal)
        midiclock->stop();
}

// Initialization

void intialize_midi() 
{
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.sethandleNoteOn(handle_note_on);
    MIDI.sethandleNoteOff(handle_note_off);
    MIDI.setHandleClock(handle_clock);
    MIDI.setHandleStart(handle_start);
    MIDI.setHandleStop(handle_stop);
    MIDI.setHandleContinue(handle_continue);

    // midiclock = &Clock::getInstance();

    midi_thread = std::thread(midi_loop);
    midi_thread.join();

    println_to_console("initialized midi");
}

// Output methods

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
#include "../clock/clock.h"
#include "console.h"
#include <cstdlib>
RtMidiOut* midi_out;
RtMidiIn* midi_in;

static const int note_on=0x90;
static const int note_off=0x80;
static const int channel_message=0xEF;
static const int clock_pulse=0xF8;
static const int midi_start=0xFA;
static const int midi_continue=0xFB;
static const int midi_stop=0xFC;

void handle_note_off(int note, int velocity, int channel){
    //Send to effects
}
void handle_note_on(int note, int velocity, int channel){
    //Send to effects
}

void handleSongPosition(){

}

void handle_clock(){
    //Send to clock if clock internal
     if (!midiclock->internal) {
        midiclock->pulse();
        println_to_console("pulsing");
     }
}

void handle_start(){
    if (!midiclock->internal)
        midiclock->start();
}

void handle_continue(){
    //Send to clock if clock internal
}

void handle_stop(){
    //Send to clock if clock internal
    if (!midiclock->internal)
        midiclock->stop();
}

void midi_callback(double deltatime, std::vector< unsigned char > *message, void *userData)
{
    println_to_console("midi_callback");
    unsigned int nBytes = message->size();
    if (nBytes > 0) {
        int message_type = (int)message->at(0);
        int channel;
        int note;
        int velocity;
        println_to_console(message_type);
        if (message_type <= channel_message) {
            channel = message_type % 0x0F;
            message_type = message_type - channel;
        }
        switch((int)message->at(0) - channel) {
            case clock_pulse:
                handle_clock();
                break;
            case note_off:
                note = (int)message->at(1);
                velocity = (int)message->at(2);
                handle_note_on(note, velocity, channel);
                break;
            case note_on:
                note = (int)message->at(1);
                velocity = (int)message->at(2);
                handle_note_on(note, velocity, channel);
                break;
            case midi_start:
                handle_start();
                break;
            case midi_continue:
                handle_continue();
                break;
            case midi_stop:
                handle_stop(); 
                break; 
        }
    }
}


void intialize_midi() 
{
    print_to_console("initializing midi");
    midi_out = new RtMidiOut();
    midi_in = new RtMidiIn();
    try {
        midi_out->openVirtualPort();
        println_to_console("opened outport");
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        println_to_console("failed to create outport");
    }
    try {
        midi_in->openVirtualPort();
        midi_in->setCallback(&midi_callback);
        midi_in->ignoreTypes(false, false, false);
        println_to_console("opened inport");
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        println_to_console("failed to create inport");
    }
    
}

void send_midi_note(bool on, int note, int velocity, int channel) 
{
    std::vector<unsigned char> message;
    if (on) {
        message.push_back(note_on+channel);
        message.push_back(note);
        message.push_back(velocity);
        midi_out->sendMessage( &message );
        print_to_console("Sent note");
        println_to_console(note);
    } else {
        message.push_back(note_off+channel);
        message.push_back(note);
        message.push_back(velocity);
        midi_out->sendMessage( &message );
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
    midi_out->sendMessage( &message );
}

#endif



