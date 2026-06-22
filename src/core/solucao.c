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

Solucao* criar_solucao(int initial_cap)
{
    Solucao *s = malloc(sizeof(Solucao));

    s->qtd_bins = 0;
    s->cap_bins = initial_cap;

    s->bins = malloc(sizeof(Bin) * initial_cap);

    return s;
}

void adicionar_item_bin(Bin *bin, int item, int peso)
{
    bin->objetos[bin->qtd_objetos++] = item;
    bin->capacidade_usada += peso;
}

void remover_item(Bin *b, int pos, int peso)
{
    for (int i = pos; i < b->qtd_objetos - 1; i++)
        b->objetos[i] = b->objetos[i + 1];

    b->qtd_objetos--;
    b->capacidade_usada -= peso;

    if (b->qtd_objetos == 0)
        b->capacidade_usada = 0;
}

void compactar_bins(Solucao *s)
{
    int k = 0;

    for (int i = 0; i < s->qtd_bins; i++)
    {
        if (s->bins[i].qtd_objetos > 0)
        {
            if (k != i)
            {
                // move struct inteiro (OK porque cada Bin é dono do seu heap)
                s->bins[k] = s->bins[i];
            }
            k++;
        }
        else
        {
            free(s->bins[i].objetos);
            s->bins[i].objetos = NULL;
            s->bins[i].qtd_objetos = 0;
            s->bins[i].capacidade_usada = 0;
        }
    }

    s->qtd_bins = k;
}

Bin copiar_bin(const Bin *b)
{
    Bin c;

    c.qtd_objetos = b->qtd_objetos;
    c.capacidade_usada = b->capacidade_usada;

    c.objetos = malloc(sizeof(int) * MAX_BINS);

    if (b->qtd_objetos > 0)
    {
        memcpy(
            c.objetos,
            b->objetos,
            sizeof(int) * b->qtd_objetos
        );
    }

    return c;
}
Solucao* copiar_solucao(const Solucao *orig)
{
    Solucao *copia = malloc(sizeof(Solucao));

    if (!copia)
        return NULL;


    copia->qtd_bins = orig->qtd_bins;


    copia->bins = malloc(sizeof(Bin) * MAX_BINS);


    if (!copia->bins)
    {
        free(copia);
        return NULL;
    }


    for (int i = 0; i < orig->qtd_bins; i++)
    {
        copia->bins[i] = copiar_bin(&orig->bins[i]);
    }


    return copia;
}

void liberar_solucao(Solucao *s)
{
    if (!s) return;

    for (int i = 0; i < s->qtd_bins; i++)
    {
        free(s->bins[i].objetos);
    }

    free(s->bins);
    free(s);
}

static void garantir_capacidade_bins(Solucao *s)
{
    if (s->qtd_bins < s->cap_bins)
        return;

    s->cap_bins *= 2;

    s->bins = realloc(s->bins, sizeof(Bin) * s->cap_bins);
}

int custo(const Solucao *s)
{
    return s->qtd_bins;
}

 int adicionar_bin(Solucao *s)
{
    garantir_capacidade_bins(s);

    Bin *b = &s->bins[s->qtd_bins];

    b->qtd_objetos = 0;
    b->capacidade_usada = 0;
    b->objetos = malloc(sizeof(int) * MAX_BINS); // or inst->n

    return s->qtd_bins++;
}

int solucao_valida(const Solucao *s, const Instancia *inst)
{
    for (int i = 0; i < s->qtd_bins; i++)
    {
        int soma = 0;

        for (int j = 0; j < s->bins[i].qtd_objetos; j++)
        {
            int item = s->bins[i].objetos[j];
            soma += inst->pesos[item];
        }

        if (soma > inst->capacidade)
            return 0;
    }

    return 1;
}

void print_bins(Solucao *s, Instancia *inst)
{
    for (int i = 0; i < s->qtd_bins; i++)
    {
        for (int j = 0; j < s->bins[i].qtd_objetos; j++)
        {
            printf("%d,", inst->pesos[s->bins[i].objetos[j]]);
        }
        printf("\t");
    }

    printf("\n");
}