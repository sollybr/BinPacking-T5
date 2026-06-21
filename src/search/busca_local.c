#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "search/busca_local.h"

static Solucao* copiar(Solucao *s)
{
    Solucao *c = malloc(sizeof(Solucao));

    c->qtd_bins = s->qtd_bins;

    c->bins = malloc(sizeof(Bin) * s->qtd_bins);

    for(int i = 0; i < s->qtd_bins; i++)
    {
        c->bins[i] = s->bins[i];

        c->bins[i].objetos =
            malloc(sizeof(int) * s->bins[i].qtd_objetos);

        for(int j = 0; j < s->bins[i].qtd_objetos; j++)
        {
            c->bins[i].objetos[j] =
                s->bins[i].objetos[j];
        }
    }

    return c;
}

static void liberar(Solucao *s)
{
    if(!s) return;

    for(int i = 0; i < s->qtd_bins; i++)
        free(s->bins[i].objetos);

    free(s->bins);
    free(s);
}


static void remover_item(Bin *b, int pos)
{
    for(int i = pos; i < b->qtd_objetos - 1; i++)
        b->objetos[i] = b->objetos[i + 1];

    b->qtd_objetos--;
}


Solucao* busca_local_exaustiva(Solucao *inicio, double tempo_max)
{
    clock_t start = clock();

    Solucao *atual = copiar(inicio);

    int melhorou = 1;

    while(melhorou)
    {
        melhorou = 0;

        Solucao *melhor_global = copiar(atual);
        int melhor_custo = custo(atual);

        for(int i = 0; i < atual->qtd_bins; i++)
        {
            for(int j = 0; j < atual->bins[i].qtd_objetos; j++)
            {
                int item = atual->bins[i].objetos[j];
                int peso = item;

                for(int k = 0; k < atual->qtd_bins; k++)
                {
                    if(i == k) continue;

                    double tempo =
                        (double)(clock() - start)
                        / CLOCKS_PER_SEC;

                    if(tempo > tempo_max)
                        return atual;

                    Solucao *novo = copiar(atual);

                    Bin *origem = &novo->bins[i];
                    Bin *dest = &novo->bins[k];

                    if(dest->capacidade_usada + peso
                        <= 1000000)   // placeholder capacity
                    {
                        remover_item(origem, j);

                        dest->objetos[dest->qtd_objetos++] = item;

                        dest->capacidade_usada += peso;
                        origem->capacidade_usada -= peso;

                        int c = custo(novo);

                        if(c < melhor_custo)
                        {
                            liberar(melhor_global);
                            melhor_global = novo;
                            melhor_custo = c;
                            melhorou = 1;
                        }
                        else
                        {
                            liberar(novo);
                        }
                    }
                    else
                    {
                        liberar(novo);
                    }
                }
            }
        }

        if(melhorou)
        {
            liberar(atual);
            atual = copiar(melhor_global);
        }

        liberar(melhor_global);
    }

    return atual;
}