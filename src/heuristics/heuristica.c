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

static void adicionar_item_bin(
        Bin *bin,
        int item,
        int peso)
{

    bin->objetos[bin->qtd_objetos] = item;

    bin->qtd_objetos++;

    bin->capacidade_usada += peso;

}

static Bin criar_bin()
{

    Bin b;

    b.capacidade_usada = 0;

    b.qtd_objetos = 0;

    b.objetos = malloc(sizeof(int) * MAX_BINS);


    return b;
}

Solucao* first_fit(Instancia *inst)
{

    Solucao *sol = criar_solucao(inst->n);

    for(int i = 0; i < inst->n; i++)
    {

        int peso = inst->pesos[i];

        int colocado = 0;



        for(int j = 0; j < sol->qtd_bins; j++)
        {

            Bin *b = &sol->bins[j];


            if(
                b->capacidade_usada + peso
                <= inst->capacidade
              )
            {

                adicionar_item_bin(
                    b,
                    i,
                    peso
                );


                colocado = 1;

                break;
            }

        }

        if(!colocado)
        {

            sol->bins[sol->qtd_bins]
                = criar_bin();


            adicionar_item_bin(
                &sol->bins[sol->qtd_bins],
                i,
                peso
            );


            sol->qtd_bins++;

        }

    }


    return sol;
}


Solucao* best_fit(Instancia *inst)
{

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

            sol->bins[sol->qtd_bins]
                = criar_bin();


            adicionar_item_bin(
                &sol->bins[sol->qtd_bins],
                i,
                peso
            );


            sol->qtd_bins++;

        }

    }


    return sol;

}
