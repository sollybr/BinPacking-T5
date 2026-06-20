#ifndef HEURISTICA_H
#define HEURISTICA_H

#include "instancia.h"

#define MAX_BINS 10000

typedef struct {

    int quantidade;

    int capacidade_usada;

    int *objetos;

    int qtd_objetos;

} Bin;


typedef struct {

    Bin *bins;

    int qtd_bins;


} Solucao;

Heuristica escolher_heuristica();

typedef Solucao* (*Heuristica)(Instancia *);


Solucao* first_fit(Instancia *inst);


Solucao* best_fit(Instancia *inst);


void liberar_solucao(Solucao *sol);


#endif