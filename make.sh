#!/bin/bash
sh ./res/vendor/modify.sh
sh ./res/assets.sh
cmake . -G "MinGW Makefiles"
mingw32-make
printf "\n"
read -n 1 -s -r -p "Press any key to continue"
