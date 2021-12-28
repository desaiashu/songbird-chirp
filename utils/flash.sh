#!/bin/zsh
set -e #exit if any command fails
T="$(date +%s)"

libs=(
    arrangement
    clock
    composition
    effects
    interface
    midifile
    notes
    sequencing
    theory
    voices
)
    
# Update libraries
echo "Copying updated libraries"
for l in ${libs[@]}; do
  rm -rf ~/Documents/Arduino/libraries/${l}
  cp -r libraries/${l} ~/Documents/Arduino/libraries
done

# Compile
echo "Compiling"
arduino-cli compile --fqbn $1 songbird-chirp 

T="$(($(date +%s)-T))"
echo "$(tput bold)Compiling finished in ${T} seconds!$(tput sgr0)"
T="$(date +%s)"

# Flash on chip
echo "Flashing"
arduino-cli upload -p $2 --fqbn $1 songbird-chirp

T="$(($(date +%s)-T))"
echo "$(tput bold)Flashing finished in ${T} seconds!$(tput sgr0)"

# Monitor serial port
echo "Monitoring"
arduino-cli monitor -p $3