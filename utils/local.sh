#!/bin/zsh
set -e #exit if any command fails
T="$(date +%s)"

# Compile w/ args from tasks.json
clang++ $@

T="$(($(date +%s)-T))"
tput bold
echo "$(tput bold)Compiling finished in ${T} seconds!$(tput sgr0)"