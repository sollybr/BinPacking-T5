cmake_minimum_required(VERSION 3.15)

project(BinPacking C)

set(PROJECT_TEAM "Equipe 5")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(binpacking
    src/app/main.c

    src/core/instancia.c
    src/core/solucao.c

    src/heuristics/heuristica.c

    src/search/busca_local.c
    src/search/multistart.c

    src/utils/config.c
    src/utils/shuffle.c
)

target_include_directories(binpacking PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/heuristics
    ${CMAKE_SOURCE_DIR}/src/search
    ${CMAKE_SOURCE_DIR}/src/utils
)
