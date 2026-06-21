#ifndef HEURISTICA_H
#define HEURISTICA_H

#include "core/instancia.h"
#include "core/solucao.h"

#define MAX_BINS 10000

typedef Solucao* (*Heuristica)(Instancia *);

Heuristica escolher_heuristica();

Solucao* first_fit(Instancia *inst);

Solucao* best_fit(Instancia *inst);

#endif
