if (Get-Command ninja -ErrorAction SilentlyContinue) {
    $gen = "Ninja"
}
elseif (Get-Command gcc -ErrorAction SilentlyContinue) {
    $gen = "MinGW Makefiles"
}
else {
    Write-Host "No toolchain found."
    exit 1
}

cmake -S . -B build -G $gen
cmake --build build