#if ARDUINO

#include <Arduino.h>
#include <FFat.h>
#include <display.h>
#include <console.h>
#include <midi_io.h>
#include <program.h>
#include <clock.h>
#include <string.h>
// #include <display.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

Display* disp;
Program* program;
int counter = 1;

bool button_1_pressed = false;
bool button_2_pressed = false;
bool button_3_pressed = false;

// TODO: move button code into buttons class
#define BUTTON_A  1
#define BUTTON_B  38
#define BUTTON_C  33

void setup() {
  
  Serial.begin(115200);

  print_to_console("Setup");

  if(!FFat.begin(true)){
    Serial.println("FFat Mount Failed");
  } else {
    Serial.println("File System Mounted");
  }

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

/////////////////////////////
  // Serial.println("128x64 OLED FeatherWing test");
  // delay(250); // wait for the OLED to power up
  // display.begin(0x3C, true); // Address 0x3C default

  // Serial.println("OLED begun");

  // // Show image buffer on the display hardware.
  // // Since the buffer is intialized with an Adafruit splashscreen
  // // internally, this will display the splashscreen.
  // display.display();
  // delay(1000);

  // // Clear the buffer.
  // display.clearDisplay();
  // display.display();

  // display.setRotation(1);
  // Serial.println("Button test");

  // // text display tests
  // display.setTextSize(1);
  // display.setTextColor(SH110X_WHITE);
  // display.setCursor(0,0);
  // display.print("Connecting to SSID\n'adafruit':");
  // display.print("connected!");
  // display.println("IP: 10.0.1.23");
  // display.println("Sending val #0");
  // display.display(); // actually display all of the above
/////////////////////

  // disp = 
  disp = new Display(&display);
  program = new Program(effects_program, disp);

  // // program = new Program(electronica_program);
  // program = new Program(effects_program, disp);
  midiclock->internal = true;
  intialize_midi();
  // midiclock->start();



}

void loop() {


  read_midi();

  if(!digitalRead(BUTTON_A)) {
    button_1_pressed = true;
  } else if (button_1_pressed) {
    program->button_callback(1);
    button_1_pressed = false;
    // display.print("A");
    // Serial.println("A");
  }

  if(!digitalRead(BUTTON_B)) {
    button_2_pressed = true;
  } else if (button_2_pressed) {
    program->button_callback(2);
    button_2_pressed = false;
    // display.print("B");
    // Serial.println("B");
  }

  if(!digitalRead(BUTTON_C)) {
    button_3_pressed = true;
  } else if (button_3_pressed) {
    program->button_callback(3);
    button_3_pressed = false;
    // display.print("C");
    // Serial.println("C");
  }

  disp->refresh_display();


  // disp->set_label(3, std::to_string(counter));

  // delay(10);
  // yield();
  
  // disp->update_display();

  // Serial.print(stp);
  // if (stp == 0) {
  //   setup();
  //   stp = 1;
  // }

  // delay(10);
}

#endif

// import time
// import songbird.interface.program as program
// from songbird.clock.clock import clock

// # Run loop
// while True:
//     program.handler()
//     clock.handler()
