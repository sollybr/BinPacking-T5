#ifndef MULTISTART_H
#define MULTISTART_H

#include "config.h"
#include "heuristica.h"
#include "busca_local.h"

Solucao* multistart(
    Instancia *inst,
    Config cfg
);

#endif