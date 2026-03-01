#!/bin/bash
# Minimal comments as requested.

echo "[+] Installing dependencies..."
sudo apt update
sudo apt install -y build-essential git cmake libraylib-dev \
    libasound2-dev libx11-dev libxrandr-dev libxi-dev \
    libxcursor-dev libxinerama-dev libgl1-mesa-dev

echo "[+] Compiling the game..."
make clean && make

if [ -f "MyGame" ]; then
    echo "[+] Done! Run with ./DuckGame"
else
    echo "[-] Build failed."
fi