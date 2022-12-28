## Setup Guide (macOS)

1. **Run install script**
```
./setup.sh
```
This install script auto installs:

- Arduino CLI the Arduino CLI to /usr/local/bin.
    - *Assumes /usr/local/bin is included in PATH file*
    - *Assumes Arduino library path is ~/Documents/Arduino/libraries*
- Arduino Core for ESP32/ESP32-S2
- Arduino libraries

2. **Install (Visual Studio Code)[https://code.visualstudio.com] and extensions**

    - Arduino
    - C/C++
    - C/C++ Themes
    - Better C++ Syntax
    - C/C++ Helper
    - C/C++ Snippets
    - Atom One Dark
    - Atom One Light

3. **Add build shortcuts**

Add keyboard shortcuts from ```utils/build_bindings.json``` to VSCode's ```keybindings.json```. 

*VSCode shortcuts are saved on a user basis not project basis, so you can customize shortcuts for build tasks.*

## Build instructions

**Building locally on macOS**

1. Use ```Command-R``` to build locally on macOS.

**Debugging on macOS**

1. Use ```Command-B``` to debug locally on macOS.

**Building on Feather board**

1. Use ```Shift-Command-E``` to change intellisense to Arduino config
2. Change port in tasks.json to match port of feather board (click port name on bottom right of VSCode to view active ports). For ex ```/dev/cu.usbmodem14301```
3. Use ```Shift-Command-R``` to build on Feather Board

**Flashing files to Feather board**

1. Put Feather board into bootloader mode by holding ```Boot``` pressing and releasing ```Reset``` then releasing ```Boot```
2. Use ```Shift-Command-Alt-F``` to flash contents of ```files``` folder to Feather board

## Additional config info

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
- Arduino Midi Library
- Adafruit BusIO
- Adafruit SH110X
- Adafruit GFX
