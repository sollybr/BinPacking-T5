#ifndef MULTISTART_H
#define MULTISTART_H

#include "utils/config.h"
#include "utils/shuffle.h"
#include "heuristics/heuristica.h"
#include "search/busca_local.h"

Solucao* multistart(
    Instancia *inst,
    Config cfg
);

#endif