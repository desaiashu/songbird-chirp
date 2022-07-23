#ifndef INTERFACE_DISPLAY
#define INTERFACE_DISPLAY

#include <string>
using std::string;

#ifdef ARDUINO
#include <Arduino.h>
#include <FFat.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#endif

class Display {
    private:
        int test;
        string label_1;
        string label_2;
        string label_3;

    public:
        Display(Adafruit_SH1107* disp);
        void set_label(int label, const string text);
        void update_display();
        Adafruit_SH1107* display;
        void refresh_display();

        // static Display& getInstance()
        // {
        //     static Display instance;
        //     return instance;
        // }
};

// #ifndef DISPLAY_IO
// #define DISPLAY_IO
// static Display* dd = &Display::getInstance();
// #endif // !DISPLAY_IO

#endif // INTERFACE_DISPLAY
