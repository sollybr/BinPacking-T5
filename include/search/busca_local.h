#ifndef BUSCA_LOCAL_H
#define BUSCA_LOCAL_H

#include "heuristics/heuristica.h"

Solucao* busca_local_exaustiva(
    Solucao *inicio,
    double tempo_max
);

#endif