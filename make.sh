#!/bin/bash

# Check and modify gitmodules and assets
sh ./res/vendor/modify.sh
sh ./res/assets.sh

# Build the project with CMake
mkdir -p log
cmake . -G "MinGW Makefiles"
mingw32-make

# Exit by pressing any key
printf "\n"
read -n 1 -s -r -p "Press any key to continue"
