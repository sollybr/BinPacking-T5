#ifndef HEURISTICA_H
#define HEURISTICA_H

#include "core/solucao.h"
#include "core/instancia.h"

typedef Solucao* (*Heuristica)(Instancia *);

Heuristica escolher_heuristica();

Solucao* first_fit(Instancia *inst);

Solucao* best_fit(Instancia *inst);

#endif
