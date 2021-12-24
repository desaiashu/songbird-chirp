### Dependencies:

**Toolchain**
- Mac OSX
- Arduino CLI 
-- Installed in /usr/local/bin (assuming PATH includes /usr/local/bin)
-- Assumes Arduino library path is ~/Documents/Arduino/libraries
- VSCode
-- Need to set up build task keyboard shortcut for VSCode task "build-and-flash"

**VSCode extensions**
- Arduino
- C/C++
- C/C++ Themes
- Better C++ Syntax
- C/C++ Helper
- C/C++ Snippets
- Atom One Dark
- Atom One Light

**Arduino Board Config** (via VS Code extension or CLI)
- UM FeatherS2 (esp32)
- USB CDC on Boot: Enabled
- Partition Scheme: 16M Flash (3MB APP/9MB FATFS)
- CPU Frequency: 240 MHz
- Flash Size: 16MB
- Upload Speed: 921600

**Arduino Libraries** (via VS Code extension or CLI)
- Arduino Core for ESP32 (includes ESP-IDF)
-- Need to add additional board URL for (ESP32)[https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json]
- Arduino Midi Library
- Adafruit BusIO
- Adafruit SH110X
- Adafruit GFX

**Hardware**
- FeatherS2 board by Unexpected Maker
- FeatherWing OLED - 128x64
- MIDI FeatherWing
- 3x I2C QT Rotary Encoder
- DS3231 Precision RTC (optional, needed for tight master clock)
- Quad Side-By-Side FeatherWing Kit 
