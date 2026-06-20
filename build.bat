@echo off
set BUILD_DIR=build

rmdir /s /q %BUILD_DIR% 2>nul

echo Trying Ninja...
cmake -S . -B %BUILD_DIR% -G "Ninja"

if errorlevel 1 (
    echo Ninja failed. Trying MinGW Makefiles...
    cmake -S . -B %BUILD_DIR% -G "MinGW Makefiles"

    if errorlevel 1 (
        echo ERROR: No valid generator found.
        exit /b 1
    )
)

cmake --build %BUILD_DIR%