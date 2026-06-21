#ifndef BUSCA_LOCAL_H
#define BUSCA_LOCAL_H

#include "core/solucao.h"
#include "heuristics/heuristica.h"

Solucao* busca_local_exaustiva(
    Solucao *inicio,
    Instancia *,
    double tempo_max
);

#endif