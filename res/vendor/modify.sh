#!/bin/bash
echo "Modifying files in vendor folder..."
echo "[1/2] Update gitmodules..."
git --git-dir=$(pwd)/.git submodule foreach --recursive git reset --hard
git --git-dir=$(pwd)/.git submodule update --remote --merge
echo "[2/2] Setup CMake in imgui folder..."
cp -r $(pwd)/res/vendor/imgui/. $(pwd)/vendor/imgui/
echo "Modify completed"
echo ""
