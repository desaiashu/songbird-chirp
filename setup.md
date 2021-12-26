### Setup Guide

## Mac OSX Setup Instructions

**1. Run install script**
```
./setup.sh
```
This install script installs:
- Arduino CLI the Arduino CLI to /usr/local/bin.
    - Assumes /usr/local/bin is included in PATH file
    - Assumes Arduino library path is ~/Documents/Arduino/libraries

**2. Install (Visual Studio Code)[https://code.visualstudio.com] and extensions**
    - Arduino
    - C/C++
    - C/C++ Themes
    - Better C++ Syntax
    - C/C++ Helper
    - C/C++ Snippets
    - Atom One Dark
    - Atom One Light

**3. Add build shortcuts**

Add keyboard shortcuts from utils/build_bindings.json to VSCode's keybindings.json. VSCode shortcuts are saved on a user basis not project basis, so you can customize shortcuts for build tasks.


## Additional config info
No action needed for config

**Arduino Board Config** (defaults for feathers2)
- UM FeatherS2 (esp32)
- USB CDC on Boot: Enabled
- Partition Scheme: 16M Flash (2MB APP/12.5MB FATFS)
    - If this changes, task flash-files will need updating
- CPU Frequency: 240 MHz
- Flash Size: 16MB
- Upload Speed: 921600

**Arduino Libraries**
- Arduino Core for ESP32 (includes ESP-IDF)
    - Need to add additional board URL for (ESP32)[https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json]
- Arduino Midi Library
- Adafruit BusIO
- Adafruit SH110X
- Adafruit GFX
