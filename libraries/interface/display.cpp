#include "display.h"
#include "console.h"

#if ARDUINO
#include <Arduino.h>
#include <FFat.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);


// OLED FeatherWing buttons map to different pins depending on board:
#define BUTTON_A  5
#define BUTTON_B  21
#define BUTTON_C  20


Display::Display()
{

  label_1="Scale: C minor";
  label_2="Scale Lock: off";
  label_3="Channel: 8";

  print_to_console("File Structure");
  display.begin(0x3C, true); // Address 0x3C default

  print_to_console("OLED begun");

  update_display();


  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
//  display.display();
//  delay(1000); 

  //   for (size_t i = 0; i < 5000; i++) {
  //   print_to_console("DISP");
  //   delay(400);
  // }

}

void Display::update_display()
{
    // Clear the buffer.
    display.clearDisplay();
    display.display();

    display.setRotation(1);
    print_to_console("Button test");

    pinMode(BUTTON_A, INPUT_PULLUP);
    pinMode(BUTTON_B, INPUT_PULLUP);
    pinMode(BUTTON_C, INPUT_PULLUP);

    // text display tests
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0,0);
    display.println(label_1.c_str());
    display.println(label_2.c_str());
    display.println(label_3.c_str());
    display.display(); // actually display all of the above
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


// import board
// import displayio
// import terminalio

// # can try import bitmap_label below for alternative
// from adafruit_display_text import label
// import adafruit_displayio_sh1107

// class Display:
//     def __init__(
//         self,
//         text1="",
//         text2="",
//         text3="Songbird"
//     ):
//         displayio.release_displays()
//         # oled_reset = board.D9

//         # Use for I2C
//         i2c = board.I2C()
//         display_bus = displayio.I2CDisplay(i2c, device_address=0x3C)

//         # SH1107 is vertically oriented 64x128
//         WIDTH = 128
//         HEIGHT = 64
//         BORDER = 2

//         display = adafruit_displayio_sh1107.SH1107(
//             display_bus, width=WIDTH, height=HEIGHT, rotation=0
//         )

//         # Make the display context
//         splash = displayio.Group()
//         display.show(splash)

//         # color_bitmap = displayio.Bitmap(WIDTH, HEIGHT, 1)
//         # color_palette = displayio.Palette(1)
//         # color_palette[0] = 0xFFFFFF  # White
//         #
//         # bg_sprite = displayio.TileGrid(color_bitmap, pixel_shader=color_palette, x=0, y=0)
//         # splash.append(bg_sprite)
//         #
//         # # Draw a smaller inner rectangle in black
//         # inner_bitmap = displayio.Bitmap(WIDTH - BORDER * 2, HEIGHT - BORDER * 2, 1)
//         # inner_palette = displayio.Palette(1)
//         # inner_palette[0] = 0x000000  # Black
//         # inner_sprite = displayio.TileGrid(
//         #     inner_bitmap, pixel_shader=inner_palette, x=BORDER, y=BORDER
//         # )
//         # splash.append(inner_sprite)

//         # Draw some label text
//         self.label1 = label.Label(terminalio.FONT, text=text1, color=0xFFFFFF, x=8, y=8)
//         splash.append(self.label1)

//         # Draw some label text
//         self.label2 = label.Label(terminalio.FONT, text=text2, color=0xFFFFFF, x=100, y=8)
//         splash.append(self.label2)

//         self.label3 = label.Label(terminalio.FONT, text=text3, scale=2, color=0xFFFFFF, x=9, y=44)
//         splash.append(self.label3)

//     def setLabel1(self, text):
//         self.label1.text = text

//     def setLabel2(self, text):
//         self.label2.text = text
