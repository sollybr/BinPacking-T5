#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"

#include "instancia.h"
#include "heuristica.h"
#include "shuffle.h"

Solucao* copiar_solucao(Solucao *s)
{

    Solucao *c = malloc(sizeof(Solucao));


    c->qtd_bins = s->qtd_bins;


    c->bins =
        malloc(sizeof(Bin)*MAX_BINS);



    for(int i=0;i<s->qtd_bins;i++)
    {

        c->bins[i] = s->bins[i];


        c->bins[i].objetos =
            malloc(sizeof(int)*MAX_BINS);


        for(int j=0;j<s->bins[i].qtd_objetos;j++)
        {
            c->bins[i].objetos[j]
                =
            s->bins[i].objetos[j];
        }

    }


    return c;
}


int custo(Solucao *s)
{
    return s->qtd_bins;
}


int gerar_vizinhos(
        Solucao *atual,
        Solucao **melhor,
        int limite_vizinhanca)
{

    int testados = 0;

    *melhor = atual;

    for(int i=0;i<atual->qtd_bins;i++)
    {

        for(int j=0;j<atual->bins[i].qtd_objetos;j++)
        {


            for(int destino=0;
                destino<atual->qtd_bins;
                destino++)
            {

                if(testados >= limite_vizinhanca)
                    return testados;



                if(i == destino)
                    continue;



                Solucao *novo =
                    copiar_solucao(atual);



                Bin *origem =
                    &novo->bins[i];


                Bin *dest =
                    &novo->bins[destino];



                int obj =
                    origem->objetos[j];


                if(
                dest->capacidade_usada
                + obj
                <= 1000000)
                {

                    dest->objetos[
                        dest->qtd_objetos++
                    ] = obj;



                    dest->capacidade_usada += obj;



                    origem->qtd_objetos--;

                    origem->capacidade_usada -= obj;



                    if(
                    custo(novo)
                    <
                    custo(*melhor))
                    {

                        liberar_solucao(*melhor);

                        *melhor = novo;

                    }

                    else
                    {
                        liberar_solucao(novo);
                    }

                }


                testados++;

            }
        }
    }

    return testados;
}


Solucao* busca_local(
        Solucao *inicio,
        double tempo_max,
        int tamanho_vizinhanca)
{


    clock_t inicio_tempo =
        clock();



    Solucao *atual =
        copiar_solucao(inicio);

    while(1)
    {


        double tempo =
        (double)
        (clock()-inicio_tempo)
        /
        CLOCKS_PER_SEC;



        if(tempo >= tempo_max)
            break;



        Solucao *melhor;



        gerar_vizinhos(
            atual,
            &melhor,
            tamanho_vizinhanca
        );



        if(
        custo(melhor)
        <
        custo(atual))
        {

            liberar_solucao(atual);

            atual = melhor;

        }

        else
        {

            if(melhor != atual)
                liberar_solucao(melhor);


            break;

        }

    }


    return atual;
}


int main(int argc, char** argv)
{

    srand(time(NULL));
    
    Config config;

    ler_parametros(
        argc,
        argv,
        &config
    );
    char *file_to_read;  

    if (argv == 1) file_to_read = "BP-0.txt";
    else file_to_read = argv[1];

    Instancia *inst =
        ler_instancia(file_to_read);

    int partidas = 50;

    double tempo_limite = 5.0;

    int tamanho_vizinhanca = 1000;

    Solucao *solucoes[partidas];

    for(int i=0;i<partidas;i++)
    {

        shuffle(
            inst->pesos,
            inst->n,
            sizeof(int)
        );

        Heuristica h;

        if(rand()%2) h = first_fit;

        else h = best_fit;

        Solucao *s = h(inst);

        s = busca_local(
            s,
            tempo_limite,
            tamanho_vizinhanca
        );

        solucoes[i] = s;


        printf(
            "Partida %d -> %d bins\n",
            i+1,
            custo(s)
        );

    }


    Solucao *melhor =
        solucoes[0];



    for(int i=1;i<partidas;i++)
    {

        if(
        custo(solucoes[i])
        <
        custo(melhor))
        {

            melhor =
            solucoes[i];

        }

    }



    printf(
        "\nMelhor solução: %d bins\n",
        custo(melhor)
    );




    for(int i=0;i<partidas;i++)
    {

        if(solucoes[i] != melhor)
            liberar_solucao(solucoes[i]);

    }



    liberar_solucao(melhor);


    liberar_instancia(inst);



    return 0;
}