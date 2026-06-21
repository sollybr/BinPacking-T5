#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "search/busca_local.h"

static void liberar(Solucao *s)
{
    if(!s) return;

    for(int i = 0; i < s->qtd_bins; i++)
        free(s->bins[i].objetos);

    free(s->bins);
    free(s);
}

Solucao* busca_local_exaustiva(
    Solucao *inicio,
    Instancia *inst,
    double tempo_max)
{
    clock_t start = clock();

    Solucao *atual = copiar_solucao(inicio);

    printf("[INIT] bins=%d tempo_max=%.3f\n",
           atual->qtd_bins, tempo_max);

    int melhorou = 1;

    while(melhorou)
    {
        melhorou = 0;

        Solucao *melhor_global = copiar_solucao(atual);
        int melhor_custo = custo(atual);

        Solucao *ref = atual;
        int n_bins = ref->qtd_bins;

        // for(int i = 0; i < n_bins; i++)
        // {
        //     int qtd = ref->bins[i].qtd_objetos;

        //     for(int j = 0; j < qtd; j++)
        //     {
        //         int item = ref->bins[i].objetos[j];
        //         int peso = inst->pesos[item];

        //         printf("[TRY] i=%d j=%d item=%d peso=%d bins=%d\n",
        //                i, j, item, peso, n_bins);

        //         for(int k = 0; k < n_bins; k++)
        //         {
        //             if(i == k) continue;

        //             double tempo =
        //                 (double)(clock() - start) / CLOCKS_PER_SEC;

        //             if(tempo >= tempo_max)
        //             {
        //                 printf("[TIMEOUT] i=%d j=%d k=%d elapsed=%.4f\n",
        //                        i, j, k, tempo);
        //                 return atual;
        //             }

        //             Solucao *novo = copiar_solucao(atual);

        //             Bin *origem = &novo->bins[i];
        //             Bin *dest   = &novo->bins[k];

        //             int bin_removed = 0;

        //             if(dest->capacidade_usada + peso <= inst->capacidade)
        //             {
        //                 printf("[MOVE] i=%d j=%d k=%d\n", i, j, k);

        //                 remover_item(origem, j, peso);

        //                 dest->objetos[dest->qtd_objetos++] = item;
        //                 dest->capacidade_usada += peso;

        //                 if(origem->qtd_objetos == 0)
        //                 {
        //                     remover_bin(novo, i);
        //                     bin_removed = 1;
        //                     printf("[BIN REMOVED] i=%d\n", i);
        //                 }

        //                 int c = custo(novo);

        //                 printf("[COST] current=%d best=%d bins=%d\n",
        //                        c, melhor_custo, novo->qtd_bins);

        //                 if(c < melhor_custo)
        //                 {
        //                     printf("[IMPROVE] new_best=%d\n", c);

        //                     liberar(melhor_global);
        //                     melhor_global = novo;
        //                     melhor_custo = c;
        //                     melhorou = 1;
        //                 }
        //                 else
        //                 {
        //                     liberar(novo);
        //                 }
        //             }
        //             else
        //             {
        //                 printf("[SKIP CAPACITY] i=%d j=%d k=%d\n", i, j, k);
        //                 liberar(novo);
        //             }

        //             if(bin_removed)
        //                 break;
        //         }
        //     }
        // }

        if(melhorou)
        {
            printf("[UPDATE GLOBAL]\n");
            liberar(atual);
            atual = melhor_global;
        }
        else
        {
            printf("[NO IMPROVEMENT ITERATION]\n");
            liberar(melhor_global);
        }
    }

    printf("[END] final_bins=%d\n", atual->qtd_bins);

    return atual;
}