cmake_minimum_required(VERSION 3.15)

project(BinPacking C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Include headers
include_directories(include)

# Executable
add_executable(binpacking
    main.c

    src/core/instancia.c
    src/core/solucao.c

    src/heuristics/heuristica.c

    src/search/busca_local.c
    src/search/multistart.c

    src/utils/shuffle.c
    src/utils/config.c
)