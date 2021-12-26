#!/bin/bash
T="$(date +%s)"

curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=/usr/local/bin sh
arduino-cli core install esp32:esp32 --additional-urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
arduino-cli lib install "MIDI Library"
arduino-cli lib install "Adafruit SH110X"
# Adafruit SH110X depends on and will auto-install "Adafruit BusIO" and "Adafruit GFX"

T="$(($(date +%s)-T))"
tput bold
echo "$(tput bold)Installation completed in in ${T} seconds!$(tput sgr0)"