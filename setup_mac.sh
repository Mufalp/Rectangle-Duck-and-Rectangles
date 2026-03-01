#!/bin/bash

# Check for Homebrew
if ! command -v brew &> /dev/null; then
    echo "[-] Homebrew not found."
    exit 1
fi

echo "[+] Installing Raylib via Brew..."
brew install raylib

echo "[+] Compiling..."
make clean && make

if [ -f "MyGame" ]; then
    echo "[+] Success! Run with ./DuckGame"
else
    echo "[-] Build failed."
fi