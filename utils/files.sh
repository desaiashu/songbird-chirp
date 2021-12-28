#!/bin/zsh
T="$(date +%s)"

# Create image
echo "Creating ffat image"
./utils/mkfatfs -c $1 -s $2 utils/$1.bin

echo "Checking ffat image"
./utils/mkfatfs -u utils/$1 utils/$1.bin

T="$(($(date +%s)-T))"
echo "$(tput bold)Creation finished in ${T} seconds!$(tput sgr0)"
T="$(date +%s)"

# Flash and delete image
echo "Creating flash image"
/Users/Ashu/Library/Arduino15/packages/esp32/tools/esptool_py/3.1.0/esptool --chip $3 --port $4 --baud $5 write_flash $6 utils/$1.bin

# Clearing temp files
echo "Clearing temp files"
rm utils/$1.bin
rm -rf utils/$1

T="$(($(date +%s)-T))"
echo "$(tput bold)Flashing finished in ${T} seconds!$(tput sgr0)"
T="$(date +%s)"
