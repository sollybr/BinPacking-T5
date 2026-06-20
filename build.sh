#!/bin/bash

BUILD_DIR=build

rm -rf $BUILD_DIR

echo "Trying Ninja..."

cmake -S . -B $BUILD_DIR -G "Ninja" 2>/dev/null

if [ $? -ne 0 ]; then
    echo "Ninja failed or not installed. Trying MinGW Makefiles..."

    cmake -S . -B $BUILD_DIR -G "MinGW Makefiles"

    if [ $? -ne 0 ]; then
        echo "ERROR: No valid generator found (Ninja or MinGW)."
        exit 1
    fi
fi

cmake --build $BUILD_DIR