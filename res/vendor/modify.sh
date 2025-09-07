#!/bin/bash
set -e
echo -e "\e[36mModifying files in vendor folder...\e[0m"
echo -e "\e[36m[1/2] Update gitmodules...\e[0m"
git --git-dir=$(pwd)/.git submodule foreach --recursive git reset --hard
git --git-dir=$(pwd)/.git submodule update --remote --merge
echo -e "\e[36m[2/2] Setup CMake in imgui folder...\e[0m"
cp -r $(pwd)/res/vendor/imgui/. $(pwd)/vendor/imgui/
echo -e "\e[36mModify completed\e[0m"
echo ""
