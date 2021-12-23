# Update libraries
echo "Removing cached libs"
rm -rf ~/Documents/Arduino/libraries/arrangement
rm -rf ~/Documents/Arduino/libraries/clock
rm -rf ~/Documents/Arduino/libraries/composition
rm -rf ~/Documents/Arduino/libraries/effects
rm -rf ~/Documents/Arduino/libraries/interface
rm -rf ~/Documents/Arduino/libraries/midifile
rm -rf ~/Documents/Arduino/libraries/notes
rm -rf ~/Documents/Arduino/libraries/sequencing
rm -rf ~/Documents/Arduino/libraries/theory
rm -rf ~/Documents/Arduino/libraries/voices

echo "Copying new libs"
cp -rf libraries/arrangement ~/Documents/Arduino/libraries/
cp -rf libraries/clock ~/Documents/Arduino/libraries/
cp -rf libraries/composition ~/Documents/Arduino/libraries/
cp -rf libraries/effects ~/Documents/Arduino/libraries/
cp -rf libraries/interface ~/Documents/Arduino/libraries/
cp -rf libraries/midifile ~/Documents/Arduino/libraries/
cp -rf libraries/notes ~/Documents/Arduino/libraries/
cp -rf libraries/sequencing ~/Documents/Arduino/libraries/
cp -rf libraries/theory ~/Documents/Arduino/libraries/
cp -rf libraries/voices ~/Documents/Arduino/libraries/

# Build
echo "Building"
arduino-cli compile --fqbn esp32:esp32:feathers2 songbird-chirp

# Flash on chip
echo "Flashing"
arduino-cli upload -p /dev/cu.usbmodem14101 --fqbn esp32:esp32:feathers2 songbird-chirp

# Monitor Serial
echo "Monitoring"
arduino-cli monitor -p /dev/cu.usbmodem14101