#!/usr/bin/env bash

set -euo pipefail

ROOT_DIR="$(CDPATH= cd -- "$(dirname -- "$0")/../.." && pwd)"

printf '\033[36mModifying files in vendor folder...\033[0m\n'
printf '\033[36m[1/2] Sync git submodules...\033[0m\n'

cd "$ROOT_DIR"
git submodule sync --recursive
git submodule update --init --recursive --force

printf '\033[36m[2/2] Setup CMake in imgui folder...\033[0m\n'
cp -R "$ROOT_DIR/res/vendor/imgui/." "$ROOT_DIR/vendor/imgui/"

printf '\033[36mModify completed\033[0m\n\n'
