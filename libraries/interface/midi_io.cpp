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
    MIDI.setHandleNoteOn(handle_note_on);
    MIDI.setHandleNoteOff(handle_note_off);
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


#include "rtmidi/RtMidi.h"
#include "../sequencing/clock.h"
#include "console.h"
#include <cstdlib>

static const int NOTE_ON=0x90;
static const int NOTE_OFF=0x80;
static const int CHANNEL_MESSAGE=0xEF;
static const int CLOCK_PULSE=0xF8;
static const int MIDI_START=0xFA;
static const int MIDI_CONTINUE=0xFB;
static const int MIDI_STOP=0xFC;

static RtMidiOut* midi_out = new RtMidiOut();
static RtMidiIn* midi_in = new RtMidiIn();

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
    unsigned int nBytes = message->size();
    if (nBytes > 0) {
        int message_type = (int)message->at(0);
        int channel;
        int note;
        int velocity;
        if (message_type <= CHANNEL_MESSAGE) {
            channel = message_type % 0x0F;
            message_type = message_type - channel;
        }
        switch(message_type) {
            case CLOCK_PULSE:
                handle_clock();
                break;
            case NOTE_OFF:
                note = (int)message->at(1);
                velocity = (int)message->at(2);
                handle_note_on(note, velocity, channel);
                break;
            case NOTE_ON:
                note = (int)message->at(1);
                velocity = (int)message->at(2);
                handle_note_on(note, velocity, channel);
                break;
            case MIDI_START:
                handle_start();
                break;
            case MIDI_CONTINUE:
                handle_continue();
                break;
            case MIDI_STOP:
                handle_stop(); 
                break; 
        }
    }
}

void intialize_midi() 
{
    try {
        midi_out->openVirtualPort("Songbird");
        println_to_console("opened outport");
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        println_to_console("failed to create outport");
    }
    try {
        midi_in->openVirtualPort("Songbird");
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
        message.push_back(NOTE_ON+channel);
        message.push_back(note);
        message.push_back(velocity);
        midi_out->sendMessage( &message );
        // print_to_console("Sent note");
        // println_to_console(note);
    } else {
        message.push_back(NOTE_OFF+channel);
        message.push_back(note);
        message.push_back(velocity);
        midi_out->sendMessage( &message );
        // print_to_console("Note off");
        // println_to_console(note);
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
    message.push_back(CLOCK_PULSE);
    midi_out->sendMessage( &message );
}

#endif



