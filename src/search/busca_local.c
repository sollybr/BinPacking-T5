#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "search/busca_local.h"


Solucao* busca_local_exaustiva(
    Solucao *inicio,
    Instancia *inst,
    double tempo_max)
{
    double start = (double)clock() / CLOCKS_PER_SEC;

    Solucao *atual = copiar_solucao(inicio);

    printf("[INIT] bins=%d tempo_max=%.3f\n",
           atual->qtd_bins, tempo_max);

    int melhorou = 1;

    while(melhorou)
    {
        melhorou = 0;

        Solucao *melhor_global = copiar_solucao(atual);
        int melhor_custo = custo(atual);

        int n_bins = atual->qtd_bins;

        for(int i = 0; i < n_bins; i++)
        {
            int qtd = atual->bins[i].qtd_objetos;

            for(int j = 0; j < qtd; j++)
            {
                int item = atual->bins[i].objetos[j];
                int peso = item;

                for(int k = 0; k < n_bins; k++)
                {
                    if(i == k) continue;

                    double now = (double)clock() / CLOCKS_PER_SEC;

                    if(now - start >= tempo_max)
                    {
                        Solucao *ret = copiar_solucao(atual);
                        liberar_solucao(atual);
                        liberar_solucao(melhor_global);
                        return ret;
                    }

                    Solucao *novo = copiar_solucao(atual);

                    Bin *origem = &novo->bins[i];
                    Bin *dest   = &novo->bins[k];

                    if(dest->capacidade_usada + peso <= inst->capacidade)
                    {
                        remover_item(origem, j, peso);

                        dest->objetos[dest->qtd_objetos++] = item;
                        dest->capacidade_usada += peso;

                        if(origem->qtd_objetos == 0)
                            remover_bin(novo, i);

                        int c = custo(novo);

                        if(c < melhor_custo)
                        {
                            liberar_solucao(melhor_global);
                            melhor_global = novo;
                            melhor_custo = c;
                            melhorou = 1;
                            goto NEXT;
                        }

                        liberar_solucao(novo);
                    }
                    else
                    {
                        liberar_solucao(novo);
                    }
                }
            }
        }

        NEXT:

        if(melhorou)
        {
            liberar_solucao(atual);
            atual = melhor_global;
        }
        else
        {
            liberar_solucao(melhor_global);
        }
    }

    printf("[END] final_bins=%d\n", atual->qtd_bins);

    return atual;
}