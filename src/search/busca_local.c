#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "search/busca_local.h"
#include "core/solucao.h"

static int tempo_excedido(clock_t start, double limite)
{
    return ((double)(clock() - start) / CLOCKS_PER_SEC) >= limite;
}

static void move_item(
    Solucao *s,
    int i, int j, int k,
    Instancia *inst,
    int *item_out,
    int *peso_out)
{
    int item = s->bins[i].objetos[j];
    int peso = inst->pesos[item];

    *item_out = item;
    *peso_out = peso;

    remover_item(&s->bins[i], j, peso);
    adicionar_item_bin(&s->bins[k], item, peso);
}

static void undo_move(
    Solucao *s,
    int from,
    int to,
    int item,
    int peso,
    int pos_original)
{
    remover_item(&s->bins[to],
                 s->bins[to].qtd_objetos - 1,
                 peso);

    for(int i = s->bins[from].qtd_objetos; i > pos_original; i--)
        s->bins[from].objetos[i] = s->bins[from].objetos[i - 1];

    s->bins[from].objetos[pos_original] = item;
    s->bins[from].qtd_objetos++;
    s->bins[from].capacidade_usada += peso;
}

static void compactar_bins(Solucao *s)
{
    for(int i = 0; i < s->qtd_bins; i++)
    {
        if(s->bins[i].qtd_objetos == 0)
        {
            for(int j = i; j < s->qtd_bins - 1; j++)
                s->bins[j] = s->bins[j + 1];

            s->qtd_bins--;
            i--;
        }
    }
}

Solucao* busca_local_exaustiva(
    Solucao *inicio,
    Instancia *inst,
    double tempo_max)
{
    clock_t start = clock();

    Solucao *atual = inicio;

    printf("[INIT] bins=%d tempo_max=%.3f\n",
           atual->qtd_bins, tempo_max);

    int melhorou = 1;

    while(melhorou && !tempo_excedido(start, tempo_max))
    {
        melhorou = 0;

        int best_delta = 0;
        int best_i = -1, best_j = -1, best_k = -1;

        int n_bins = atual->qtd_bins;

        for(int i = 0; i < n_bins; i++)
        {
            for(int j = 0; j < atual->bins[i].qtd_objetos; j++)
            {
                int item = atual->bins[i].objetos[j];
                int peso = inst->pesos[item];

                for(int k = 0; k < n_bins; k++)
                {
                    if(i == k) continue;

                    if(atual->bins[k].capacidade_usada + peso > inst->capacidade)
                        continue;

                    int delta = 0;

                    if(delta <= best_delta) continue;

                    best_delta = delta;
                    best_i = i;
                    best_j = j;
                    best_k = k;
                }
            }
        }

        if(best_i != -1)
        {
            int item = atual->bins[best_i].objetos[best_j];
            int peso = inst->pesos[item];

            remover_item(&atual->bins[best_i], best_j, peso);
            adicionar_item_bin(&atual->bins[best_k], item, peso);

            compactar_bins(atual);

            melhorou = 1;
        }
    }

    printf("[END] final_bins=%d\n", atual->qtd_bins);
    return atual;
}