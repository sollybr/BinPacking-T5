#ifndef BUSCA_LOCAL_H
#define BUSCA_LOCAL_H

#include "core/solucao.h"

Solucao* busca_local_exaustiva(
    Solucao *inicio,
    Instancia *inst,
    double tempo_max
);

#endif