#include "display.h"
#include "console.h"

#ifdef ARDUINO
#include <Arduino.h>
#include <FFat.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);


// OLED FeatherWing buttons map to different pins depending on board:
// #define BUTTON_A  5
// #define BUTTON_B  21
// #define BUTTON_C  20

// #define BUTTON_A  15
// #define BUTTON_B  32
// #define BUTTON_C  14

// Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire); 

Display::Display(Adafruit_SH1107* disp) : display(disp)
{

  label_1="Scale: C minor";
  label_2="Scale Lock: off";
  label_3="Channel: 8";

  delay(250);

  print_to_console("File Structure");
  // display.begin(0x3C, true); // Address 0x3C default

  print_to_console("OLED begun");

  update_display();

}

void Display::update_display()
{
    // // Clear the buffer.
    // display->clearDisplay();
    // display->display();

    // display->setRotation(1);
    // print_to_console("Button test");

    // // text display tests
    // display->setTextSize(1);
    // display->setTextColor(SH110X_WHITE);
    // display->setCursor(0,0);
    // display->println("Songbird");
    // display->println(label_1.c_str());
    // display->println(label_2.c_str());
    // display->println(label_3.c_str());
    refresh_display(); // actually display all of the above
}

void Display::refresh_display()
{
    // delay(10);
    yield();
    display->display();
}

void Display::set_label(int label, const string text)
{
    switch (label) {
      case 1:
        label_1 = text;
        break;
      case 2:
        label_2 = text;
        break;
      case 3:
        label_2 = text;
        break;
      default:
        break;
    }
    update_display();
}

#else // Mac OSX
#endif

