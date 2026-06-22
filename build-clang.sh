#!/usr/bin/env bash
set -e

BUILD_DIR="build"

echo "== Cleaning build directory =="
rm -rf "$BUILD_DIR"

echo "== Configuring with Clang + ASan =="

cmake -S . -B "$BUILD_DIR" \
    -G Ninja \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_C_FLAGS="-fsanitize=address -fno-omit-frame-pointer -g" \
    -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address"

echo "== Building =="

cmake --build "$BUILD_DIR"

echo "== Checking ASan linkage =="

ldd "$BUILD_DIR"/binpacking.exe | grep -i asan || {
    echo "WARNING: ASan runtime not found in executable"
}

echo "== Done =="