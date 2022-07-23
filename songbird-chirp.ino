#if ARDUINO

#include <Arduino.h>
#include <FFat.h>
#include <display.h>
#include <console.h>
#include <midi_io.h>
#include <program.h>
#include <clock.h>
#include <display.h>

// Display* d;
Program* program;

// TODO: move button code into buttons class
#define BUTTON_A  9
#define BUTTON_B  6
#define BUTTON_C  5

void setup() {
  
  Serial.begin(115200);

  print_to_console("Setup");

  if(!FFat.begin(true)){
    Serial.println("FFat Mount Failed");
  } else {
    Serial.println("File System Mounted");
  }

  // d = new Display();

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  // program = new Program(electronica_program);
  program = new Program(effects_program);
  midiclock->internal = true;
  intialize_midi();
  // midiclock->start();



}

void loop() {

  read_midi();

  if(!digitalRead(BUTTON_A)) 
      program.button_callback(1);
  else if(!digitalRead(BUTTON_B)) 
      program.button_callback(2);
  else if(!digitalRead(BUTTON_C)) 
      program.button_callback(3);


  // Serial.print(stp);
  // if (stp == 0) {
  //   setup();
  //   stp = 1;
  // }
  // print_to_console("foo");
  // delay(400);
}

#endif

// import time
// import songbird.interface.program as program
// from songbird.clock.clock import clock

// # Run loop
// while True:
//     program.handler()
//     clock.handler()
