#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "search/multistart.h"


static int melhor(Solucao *a, Solucao *b)
{
    return a->qtd_bins < b->qtd_bins;
}


Solucao* multistart(Instancia *inst, const Config cfg)
{
    Solucao *melhor_global = NULL;

    clock_t inicio_global = clock();

    for(int i = 0; i < cfg.partidas; i++)
    {
        double tempo_global =
            (double)(clock() - inicio_global)
            / CLOCKS_PER_SEC;

        if(tempo_global >= cfg.tempo_limite)
            break;


        Heuristica h = escolher_heuristica();

        Solucao *s = h(inst);

        s = busca_local_exaustiva(
                s,
                cfg.tempo_limite
            );


        if(melhor_global == NULL ||
           melhor(s, melhor_global))
        {
            if(melhor_global)
                liberar_solucao(melhor_global);

            melhor_global = s;
        }
        else
        {
            liberar_solucao(s);
        }

        printf("Partida %d -> %d bins\n",
               i + 1,
               s->qtd_bins);
    }

    return melhor_global;
}