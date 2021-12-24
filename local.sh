#!/bin/bash
set -e #exit if any command fails
T="$(date +%s)"

# Compile w/ args from tasks.json
clang++ $@

T="$(($(date +%s)-T))"
echo "Compilation took ${T} seconds!"
