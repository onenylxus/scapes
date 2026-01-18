#!/bin/bash
################################################################
# Scapes Launch Script
# Interactive CLI menu for launching Scapes with options
################################################################

# Default values
PRIORITY="debug"
WRITE="false"
EXECUTABLE="./scapes.exe"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m' # No Color

# Hide cursor
tput civis

# Show cursor on exit
trap 'tput cnorm; exit' INT TERM EXIT

# Clear screen function
clear_screen() {
	clear
	echo -e "${BLUE}${BOLD}╔════════════════════════════════════════╗${NC}"
	echo -e "${BLUE}${BOLD}║         SCAPES LAUNCHER v0.1.0         ║${NC}"
	echo -e "${BLUE}${BOLD}╚════════════════════════════════════════╝${NC}"
	echo ""
}

# Function to draw menu
draw_menu() {
	local title="$1"
	shift
	local options=("$@")
	local selected=$selected_index

	echo -e "${CYAN}${BOLD}$title${NC}"
	echo ""

	for i in "${!options[@]}"; do
		if [ $i -eq $selected ]; then
			echo -e "${GREEN}${BOLD} ► ${options[$i]}${NC}"
		else
			echo -e "	${options[$i]}"
		fi
	done
	echo ""
	echo -e "${YELLOW}Use ↑/↓ arrow keys to navigate, Enter to select${NC}"
}

# Function to get key input
get_key() {
	local key
	IFS= read -rsn1 key 2>/dev/null

	if [[ $key == $'\x1b' ]]; then
		read -rsn2 -t 0.1 key 2>/dev/null
		case $key in
			'[A') echo "UP" ;;
			'[B') echo "DOWN" ;;
		esac
	elif [[ $key == "" ]]; then
		echo "ENTER"
	fi
}

# Function to show priority menu
select_priority() {
	local options=("trace" "debug" "info" "warn" "error")
	local selected_index=1  # Default to debug

	# Find current selection
	for i in "${!options[@]}"; do
		if [ "${options[$i]}" == "$PRIORITY" ]; then
			selected_index=$i
			break
		fi
	done

	while true; do
		clear_screen
		draw_menu "SELECT LOGGING PRIORITY:" "${options[@]}"

		key=$(get_key)
		case $key in
			UP)
				((selected_index--))
				if [ $selected_index -lt 0 ]; then
					selected_index=$((${#options[@]} - 1))
				fi
				;;
			DOWN)
				((selected_index++))
				if [ $selected_index -ge ${#options[@]} ]; then
					selected_index=0
				fi
				;;
			ENTER)
				PRIORITY="${options[$selected_index]}"
				break
				;;
		esac
	done
}

# Function to show write logs menu
select_write() {
	local options=("Disabled (false)" "Enabled (true)")
	local selected_index=0

	if [ "$WRITE" == "true" ] || [ "$WRITE" == "1" ]; then
		selected_index=1
	fi

	while true; do
		clear_screen
		draw_menu "ENABLE LOG FILE WRITING:" "${options[@]}"

		key=$(get_key)
		case $key in
			UP)
				((selected_index--))
				if [ $selected_index -lt 0 ]; then
					selected_index=$((${#options[@]} - 1))
				fi
				;;
			DOWN)
				((selected_index++))
				if [ $selected_index -ge ${#options[@]} ]; then
					selected_index=0
				fi
				;;
			ENTER)
				if [ $selected_index -eq 0 ]; then
					WRITE="false"
				else
					WRITE="true"
				fi
				break
				;;
		esac
	done
}

# Function to show confirmation and launch
confirm_launch() {
	local options=("Launch" "Reconfigure" "Exit")
	local selected_index=0

	while true; do
		clear_screen
		echo -e "${CYAN}${BOLD}LAUNCH CONFIGURATION:${NC}"
		echo ""
		echo -e "  ${YELLOW}Priority:${NC}   $PRIORITY"
		echo -e "  ${YELLOW}Write Logs:${NC} $WRITE"
		echo -e "  ${YELLOW}Executable:${NC} $EXECUTABLE"
		echo ""
		echo -e "${CYAN}${BOLD}SELECT ACTION:${NC}"
		echo ""

		for i in "${!options[@]}"; do
			if [ $i -eq $selected_index ]; then
				echo -e "${GREEN}${BOLD} ► ${options[$i]}${NC}"
			else
				echo -e "	${options[$i]}"
			fi
		done
		echo ""
		echo -e "${YELLOW}Use ↑/↓ arrow keys to navigate, Enter to select${NC}"

		key=$(get_key)
		case $key in
			UP)
				((selected_index--))
				if [ $selected_index -lt 0 ]; then
					selected_index=$((${#options[@]} - 1))
				fi
				;;
			DOWN)
				((selected_index++))
				if [ $selected_index -ge ${#options[@]} ]; then
					selected_index=0
				fi
				;;
			ENTER)
				case $selected_index in
					0) return 0 ;; # Launch
					1) return 1 ;; # Reconfigure
					2) return 2 ;; # Exit
				esac
				;;
		esac
	done
}

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
	clear_screen
	echo -e "${RED}Error: Executable not found at '$EXECUTABLE'${NC}"
	echo "Build the project first or specify the correct path."
	tput cnorm
	exit 1
fi

# Main menu loop
while true; do
	select_priority
	select_write
	confirm_launch
	result=$?

	if [ $result -eq 0 ]; then
		# Launch
		clear_screen
		echo -e "${GREEN}${BOLD}Launching Scapes...${NC}"
		echo -e "${CYAN}Priority: $PRIORITY | Write Logs: $WRITE${NC}"
		echo -e "${BLUE}════════════════════════════════════════${NC}"
		echo ""
		tput cnorm

		# Run executable with proper TTY handling for Windows
		# Try winpty first for Windows, fallback to direct execution
		if command -v winpty &> /dev/null; then
			winpty "$EXECUTABLE" --priority="$PRIORITY" --write="$WRITE"
		else
			# Use script to force pseudo-terminal and unbuffered output
			if command -v script &> /dev/null; then
				script -q -c "$EXECUTABLE --priority=\"$PRIORITY\" --write=\"$WRITE\"" /dev/null
			else
				# Direct execution as fallback
				"$EXECUTABLE" --priority="$PRIORITY" --write="$WRITE"
			fi
		fi
		exit_code=$?

		# Display exit status
		echo ""
		echo -e "${BLUE}════════════════════════════════════════${NC}"
		if [ $exit_code -eq 0 ]; then
			echo -e "${GREEN}Scapes exited successfully (code: $exit_code)${NC}"
		else
			echo -e "${RED}Scapes exited with error (code: $exit_code)${NC}"
		fi
		exit $exit_code
	elif [ $result -eq 2 ]; then
		# Exit
		clear_screen
		echo -e "${YELLOW}Launch cancelled.${NC}"
		tput cnorm
		exit 0
	fi
	# If result is 1, loop continues to reconfigure
done
