### Dependencies:

**Toolchain**
- Mac OSX
- Arduino CLI (full instructions below)
    - Installed in /usr/local/bin (assuming PATH includes /usr/local/bin)
    - Assumes Arduino library path is ~/Documents/Arduino/libraries
- VSCode
    - Add keyboard shortcuts from utils/build_bindings.json to VSCode's keybindings.json

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
- Partition Scheme: 16M Flash (2MB APP/12.5MB FATFS)
    - If this changes, task flash-files will need updating
- CPU Frequency: 240 MHz
- Flash Size: 16MB
- Upload Speed: 921600

**Arduino Libraries** (via VS Code extension or CLI)
- Arduino Core for ESP32 (includes ESP-IDF)
    - Need to add additional board URL for (ESP32)[https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json]
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

**Arduino CLI setup instructions**
```
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=/usr/local/bin sh
arduino-cli core install esp32:esp32 --additional-urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
