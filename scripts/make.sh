#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="${BUILD_DIR:-${ROOT_DIR}/build}"
BUILD_CONFIG="${BUILD_CONFIG:-Release}"
OS_NAME="$(uname -s)"
PAUSE_ON_SUCCESS="${PAUSE_ON_SUCCESS:-0}"

if command -v cmake >/dev/null 2>&1; then
	CMAKE_BIN="cmake"
elif command -v cmake3 >/dev/null 2>&1; then
	CMAKE_BIN="cmake3"
else
	echo "Error: CMake is not installed. Install 'cmake' (or 'cmake3') and run again."
	exit 127
fi

if ! command -v bash >/dev/null 2>&1; then
	echo "Error: bash is required to run resource setup scripts."
	exit 127
fi

cd "$ROOT_DIR"

CMAKE_CONFIGURE_ARGS=()
if [[ "$OS_NAME" == MINGW* || "$OS_NAME" == MSYS* || "$OS_NAME" == CYGWIN* ]]; then
	# Prefer Ninja on Windows shells to avoid generator mismatches with Makefiles.
	if [[ -z "${CMAKE_GENERATOR:-}" ]] && command -v ninja >/dev/null 2>&1; then
		CMAKE_CONFIGURE_ARGS+=("-G" "Ninja")
	fi
elif [[ "$OS_NAME" == "Linux" ]]; then
	has_wayland_scanner=false
	has_wayland_pkg=false
	has_x11=false
	has_opengl=false

	if command -v wayland-scanner >/dev/null 2>&1; then
		has_wayland_scanner=true
	fi
	if command -v pkg-config >/dev/null 2>&1 && pkg-config --exists wayland-client; then
		has_wayland_pkg=true
	fi
	if command -v pkg-config >/dev/null 2>&1 && pkg-config --exists x11; then
		has_x11=true
	fi
	if command -v pkg-config >/dev/null 2>&1 && (pkg-config --exists gl || pkg-config --exists opengl); then
		has_opengl=true
	elif [[ -f /usr/include/GL/gl.h || -f /usr/include/GL/glcorearb.h ]]; then
		has_opengl=true
	fi

	if [[ "$has_wayland_scanner" != true || "$has_wayland_pkg" != true ]]; then
		echo "Notice: Wayland build dependencies not fully available, disabling GLFW Wayland backend."
		CMAKE_CONFIGURE_ARGS+=("-DGLFW_BUILD_WAYLAND=OFF")
	fi

	if [[ "$has_x11" != true ]]; then
		echo "Notice: X11 development files not found, disabling GLFW X11 backend."
		CMAKE_CONFIGURE_ARGS+=("-DGLFW_BUILD_X11=OFF")
	fi

	if [[ "$has_x11" != true && ( "$has_wayland_scanner" != true || "$has_wayland_pkg" != true ) ]]; then
		echo "Error: No supported Linux GLFW backend dependencies detected."
		echo "Install one of these and run again:"
		echo "  - X11 path: libx11-dev (or distro equivalent)"
		echo "  - Wayland path: wayland-scanner + wayland-client development package"
		echo "Examples:"
		echo "  - Debian/Ubuntu: sudo apt install build-essential cmake pkg-config libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev"
		echo "  - Fedora: sudo dnf install @development-tools cmake pkgconf-pkg-config libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel"
		echo "  - Arch: sudo pacman -S base-devel cmake pkgconf libx11 libxrandr libxinerama libxcursor libxi"
		exit 1
	fi

	if [[ "$has_opengl" != true ]]; then
		echo "Error: OpenGL development files not found."
		echo "Install OpenGL dev packages and run again:"
		echo "  - Debian/Ubuntu: sudo apt install libgl1-mesa-dev"
		echo "  - Fedora: sudo dnf install mesa-libGL-devel"
		echo "  - Arch: sudo pacman -S mesa"
		exit 1
	fi
fi

# Sync vendor/assets metadata before configuring.
bash ./scripts/modify.sh
bash ./scripts/assets.sh

mkdir -p ./log

echo "Configuring project in: $BUILD_DIR"
"$CMAKE_BIN" -S "$ROOT_DIR" -B "$BUILD_DIR" "${CMAKE_CONFIGURE_ARGS[@]}" \
	-DCMAKE_RUNTIME_OUTPUT_DIRECTORY="$ROOT_DIR"

echo "Building project (config: $BUILD_CONFIG)"
"$CMAKE_BIN" --build "$BUILD_DIR" --config "$BUILD_CONFIG"

# Pause only when explicitly requested.
if [[ "$PAUSE_ON_SUCCESS" == "1" ]] && [ -t 0 ]; then
	printf "\n"
	read -r -n 1 -s -p "Build complete. Press any key to continue"
	printf "\n"
fi
