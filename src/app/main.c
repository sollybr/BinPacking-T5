#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils/config.h"
#include "utils/shuffle.h"

#include "core/solucao.h"
#include "core/instancia.h"
#include "heuristics/heuristica.h"
#include "search/multistart.h"

int main(int argc, char** argv)
{
    srand(time(NULL));

    Config config;
    ler_parametros(argc, argv, &config);

    Instancia *inst = ler_instancia(argv[1]);

    Solucao *best = multistart(inst, config);

    printf("Melhor solução: %d bins\n", custo(best));

    liberar_solucao(best);
    liberar_instancia(inst);

    return 0;
}