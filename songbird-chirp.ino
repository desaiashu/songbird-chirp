#include <Arduino.h>
#include <display.h>
#include <console.h>

Display* d;
int stp = 0;

void setup() {
  
  Serial.begin(115200);
  d = new Display();
  // d.setLabel1("foo");
  print_to_console("yay");

  stp = 1;

}

void loop() {
  Serial.print(stp);
  if (stp == 0) {
    setup();
    stp = 1;
  }
  print_to_console("foo");
  delay(400);
}


// import time
// import songbird.interface.program as program
// from songbird.clock.clock import clock

// # Run loop
// while True:
//     program.handler()
//     clock.handler()
