#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils/config.h"

#include "core/solucao.h"
#include "core/instancia.h"
#include "heuristics/heuristica.h"
#include "search/multistart.h"

void printinstancia(Instancia *inst){
    for (size_t i = 0; i < inst->n; i++)
    {
        printf("%d ", inst->pesos[i]);
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    Config config;
    ler_parametros(argc, argv, &config);

    Instancia *inst = ler_instancia(argv[1]);

    printinstancia(inst);
    
    Solucao *best = multistart(inst, config);

    printf("Melhor solucao: %d bins\n", custo(best));

    liberar_solucao(best);
    liberar_instancia(inst);

    return 0;
}