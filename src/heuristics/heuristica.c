#include <stdio.h>
#include <stdlib.h>

#include "heuristics/heuristica.h"

Heuristica escolher_heuristica()
{
    if(rand() % 2)
        return first_fit;
    else
        return best_fit;
}

Solucao* first_fit(Instancia *inst)
{
    printf("first_fit ");
    Solucao *sol = criar_solucao(inst->n);

    for(int i = 0; i < inst->n; i++)
    {

        int peso = inst->pesos[i];

        int colocado = 0;

        for(int j = 0; j < sol->qtd_bins; j++)
        {

            Bin *b = &sol->bins[j];

            if(b->capacidade_usada + peso <= inst->capacidade)
            {

                adicionar_item_bin( b,i,peso);

                colocado = 1;

                break;
            }

        }

        if(!colocado)
        {

            int idx = adicionar_bin(sol);

            adicionar_item_bin(&sol->bins[idx], i, peso);

        }

    }

    return sol;
}


Solucao* best_fit(Instancia *inst)
{
        printf("best_fit ");

    Solucao *sol = criar_solucao(inst->n);

    for(int i = 0; i < inst->n; i++)
    {

        int peso = inst->pesos[i];

        int melhor_bin = -1;

        int menor_sobra = inst->capacidade + 1;

        for(int j = 0; j < sol->qtd_bins; j++)
        {

            Bin *b = &sol->bins[j];

            int sobra =
                inst->capacidade
                -
                (b->capacidade_usada + peso);

            if(
                sobra >= 0 &&
                sobra < menor_sobra
              )
            {

                menor_sobra = sobra;

                melhor_bin = j;

            }

        }

        if(melhor_bin != -1)
        {

            adicionar_item_bin(
                &sol->bins[melhor_bin],
                i,
                peso
            );

        }

        else
        {

            int idx = adicionar_bin(sol);

            adicionar_item_bin(&sol->bins[idx], i, peso);       

        }

    }

    return sol;

}
