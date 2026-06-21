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

    int *pesos_reordenados = inst->pesos;

    for(int i = 0; i < cfg.partidas; i++)
    {
        double tempo_global =
            (double)(clock() - inicio_global)
            / CLOCKS_PER_SEC;

        if(tempo_global >= cfg.tempo_limite)
            break;

        shuffle(
            pesos_reordenados,
            inst->n,
            sizeof(int)
        );

        inst->pesos = pesos_reordenados;

        Heuristica h = escolher_heuristica();

        Solucao *s = h(inst);

        s = busca_local_exaustiva(s, inst, cfg.tempo_limite);

        printf("Partida %d -> %d bins\t",
               i + 1,
               s->qtd_bins);
               
        Bin * bin = s->bins;
        print_bins(s, inst);

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

    }

    return melhor_global;
}