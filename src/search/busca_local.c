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
    double start = (double)clock() / CLOCKS_PER_SEC;


    Solucao *atual = inicio;


    printf("[INIT] bins=%d tempo_max=%.3f\n",
           atual->qtd_bins,
           tempo_max);



    int melhorou = 1;


    while(melhorou && !tempo_excedido(start, tempo_max))
    {
        melhorou = 0;


        int best_delta = 0;

        int best_i = -1;
        int best_j = -1;
        int best_k = -1;



        int n_bins = atual->qtd_bins;



        for(int i = 0; i < n_bins; i++)
        {
            for(int j = 0; j < atual->bins[i].qtd_objetos; j++)
            {

                int item = atual->bins[i].objetos[j];
                int peso = inst->pesos[item];



                for(int k = 0; k < n_bins; k++)
                {

                    if(i == k)
                        continue;



                    if(atual->bins[k].capacidade_usada + peso >
                       inst->capacidade)
                        continue;



                    printf("[TEST] item=%d bin %d -> bin %d\n",
                           item,
                           i,
                           k);



                    /*
                        cria vizinho temporário
                    */

                    Solucao *teste = copiar_solucao(atual);
                        printf("       copied OK\n");


                    int bins_before = teste->qtd_bins;



                    move_item(
                        teste,
                        i,
                        j,
                        k,
                        inst,
                        &item,
                        &peso
                    );



                    compactar_bins(teste);



                    int bins_after = teste->qtd_bins;



                    int delta = bins_before - bins_after;



                    printf("       delta=%d (%d -> %d bins)\n",
                           delta,
                           bins_before,
                           bins_after);



                    if(delta > best_delta)
                    {
                        printf("       NEW BEST MOVE\n");


                        best_delta = delta;

                        best_i = i;
                        best_j = j;
                        best_k = k;
                    }



                    liberar_solucao(teste);
                    printf("       freed OK\n");
                }
            }
        }



        if(best_i != -1)
        {

            int item = atual->bins[best_i].objetos[best_j];
            int peso = inst->pesos[item];



            printf("[MOVE] item=%d bin %d -> bin %d improvement=%d\n",
                   item,
                   best_i,
                   best_k,
                   best_delta);



            move_item(
                atual,
                best_i,
                best_j,
                best_k,
                inst,
                &item,
                &peso
            );


            compactar_bins(atual);



            melhorou = 1;
        }
    }



    printf("[END] final_bins=%d\n",
           atual->qtd_bins);



    return atual;
}