#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
RES_DIR="$ROOT_DIR/res"

folders=(
	"skybox"
	"textures"
)
images=(
	"skybox/back.png"
	"skybox/bottom.png"
	"skybox/front.png"
	"skybox/left.png"
	"skybox/right.png"
	"skybox/top.png"
	"textures/gaseous.png"
	"textures/liquid.png"
	"textures/solid.png"
)
echo -e "\e[36mModifying files in res folder...\e[0m"
echo -e "\e[36m[1/2] Check for missing folders...\e[0m"
for folder in "${folders[@]}"; do
	if [ ! -d "$RES_DIR/$folder" ]; then
		mkdir -p "$RES_DIR/$folder"
		echo -e "\e[32mCreated folder: $folder\e[0m"
	else
		echo "Found folder: $folder"
	fi
done
echo -e "\e[36m[2/2] Check for missing images...\e[0m"
for image in "${images[@]}"; do
	img="$RES_DIR/$image"
	if [ ! -f "$img" ]; then
		cp "$RES_DIR/example.png" "$img"
		echo -e "\e[32mCreated image: $img\e[0m"
	else
		echo "Found image: $img"
	fi
done
echo -e "\e[36mModify completed\e[0m"
echo ""
