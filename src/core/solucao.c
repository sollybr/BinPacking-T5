#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/solucao.h"

Solucao* criar_solucao(int max_bins)
{
    Solucao *s = malloc(sizeof(Solucao));

    if(!s) return NULL;

    s->qtd_bins = 0;

    s->bins = malloc(sizeof(Bin) * max_bins);

    if(!s->bins)
    {
        free(s);
        return NULL;
    }

    return s;
}

Solucao* copiar_solucao(const Solucao *orig)
{
    Solucao *copia = malloc(sizeof(Solucao));

    copia->qtd_bins = orig->qtd_bins;

    copia->bins = malloc(sizeof(Bin) * MAX_BINS);

    for(int i = 0; i < orig->qtd_bins; i++)
    {
        copia->bins[i].capacidade_usada =
            orig->bins[i].capacidade_usada;

        copia->bins[i].qtd_objetos =
            orig->bins[i].qtd_objetos;

        copia->bins[i].objetos =
            malloc(sizeof(int) * MAX_ITENS_BIN);

        memcpy(
            copia->bins[i].objetos,
            orig->bins[i].objetos,
            sizeof(int) * orig->bins[i].qtd_objetos
        );
    }

    return copia;
}

void liberar_solucao(Solucao *s)
{
    if(!s) return;

    for(int i = 0; i < s->qtd_bins; i++)
    {
        free(s->bins[i].objetos);
    }

    free(s->bins);
    free(s);
}



/*
    Função objetivo clássica:
    minimizar número de bins
*/
int custo(const Solucao *s)
{
    return s->qtd_bins;
}



/*
    Verifica se solução respeita capacidade
*/
int solucao_valida(const Solucao *s, const Instancia *inst)
{
    for(int i = 0; i < s->qtd_bins; i++)
    {
        int soma = 0;

        for(int j = 0; j < s->bins[i].qtd_objetos; j++)
        {
            int item = s->bins[i].objetos[j];
            soma += inst->pesos[item];
        }

        if(soma > inst->capacidade)
            return 0;
    }

    return 1;
}