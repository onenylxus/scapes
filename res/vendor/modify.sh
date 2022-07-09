#!/bin/bash
echo "Modifying files in vendor folder..."
cp -r $(pwd)/res/vendor/imgui/. $(pwd)/vendor/imgui/
echo "Modify completed"
echo ""
