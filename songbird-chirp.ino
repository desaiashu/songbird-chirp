#if ARDUINO

#include <Arduino.h>
#include <FFat.h>
#include <display.h>
#include <console.h>
#include <midi_io.h>
#include <clock.h>

Display* d;

void setup() {
  
  Serial.begin(115200);

  print_to_console("Setup");

  if(!FFat.begin(true)){
    Serial.println("FFat Mount Failed");
  } else {
    Serial.println("File System Mounted");
  }

  d = new Display();
  // d.setLabel1("foo");

  midiclock->internal = false;
  intialize_midi();
  // midiclock->start();

}

void loop() {
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
