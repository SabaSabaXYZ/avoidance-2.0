#!/bin/sh

echo "Initialize CMake"
cmake .

echo "Build Linux"
make

echo "Build Windows"
./build_windows.sh

echo "Build WASM"
./build_wasm.sh

echo "Package Linux"
zip Avoidance2_Linux.zip Avoidance2

echo "Package Windows"
zip Avoidance2_Windows.zip Avoidance2.exe

echo "Package WASM"
zip Avoidance2_WASM.zip index.*

echo "Move to Downloads"
mv Avoidance2_*.zip ~/Downloads/
