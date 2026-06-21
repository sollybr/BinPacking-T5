#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/solucao.h"

 Bin criar_bin()
{
    Bin b;

    b.capacidade_usada = 0;

    b.qtd_objetos = 0;

    b.objetos = malloc(sizeof(int) * MAX_BINS);

    return b;
}

void remover_bin(Solucao *s, int pos)
{
    if(pos < 0 || pos >= s->qtd_bins)
        return;

    free(s->bins[pos].objetos);

    for(int i = pos; i < s->qtd_bins - 1; i++)
        s->bins[i] = s->bins[i + 1];

    s->qtd_bins--;

    s->bins[s->qtd_bins].objetos = NULL;
    s->bins[s->qtd_bins].qtd_objetos = 0;
    s->bins[s->qtd_bins].capacidade_usada = 0;
}

void adicionar_item_bin(Bin *bin, int item, int peso)
{
    bin->objetos[bin->qtd_objetos++] = item;
    bin->capacidade_usada += peso;
}

void remover_item(Bin *b, int pos, int peso)
{
    for(int i = pos; i < b->qtd_objetos - 1; i++)
        b->objetos[i] = b->objetos[i + 1];

    b->qtd_objetos--;
    b->capacidade_usada -= peso;
}

Solucao* criar_solucao(int max_bins)
{
    Solucao *s = malloc(sizeof(Solucao));

    if(!s) return NULL;

    s->qtd_bins = 0;

    s->bins = calloc(max_bins, sizeof(Bin));

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
    copia->bins = malloc(sizeof(Bin) * orig->qtd_bins);

    for(int i = 0; i < orig->qtd_bins; i++)
    {
        copia->bins[i].capacidade_usada = orig->bins[i].capacidade_usada;
        copia->bins[i].qtd_objetos = orig->bins[i].qtd_objetos;

        if(orig->bins[i].qtd_objetos > 0)
        {
            copia->bins[i].objetos =
                malloc(sizeof(int) * orig->bins[i].qtd_objetos);

            memcpy(
                copia->bins[i].objetos,
                orig->bins[i].objetos,
                sizeof(int) * orig->bins[i].qtd_objetos
            );
        }
        else
        {
            copia->bins[i].objetos = NULL;
        }
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

int custo(const Solucao *s)
{
    return s->qtd_bins;
}

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

void print_bins(Solucao * s, Instancia * inst){
    Bin * bin = s->bins;
        for (int i = 0; i < s->qtd_bins; i++)
        {
            for (int j = 0; j < (bin+i)->qtd_objetos; j++)
            {
                printf("%d,", inst->pesos[((bin+i)->objetos)[j]]);
            }
            printf("\t");
        }
    printf("\n");
}
