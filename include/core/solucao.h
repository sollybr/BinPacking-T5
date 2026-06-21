#ifndef SOLUCAO_H
#define SOLUCAO_H

#include "core/instancia.h"

#define MAX_BINS 10000
#define MAX_ITENS_BIN 10000

typedef struct {

    int capacidade_usada;
    int qtd_objetos;
    int *objetos;

} Bin;


typedef struct {

    Bin *bins;
    int qtd_bins;

} Solucao;


Solucao* criar_solucao(int max_bins);

Solucao* copiar_solucao(const Solucao *s);

void liberar_solucao(Solucao *s);

int custo(const Solucao *s);

int solucao_valida(const Solucao *s, const Instancia *inst);


#endif