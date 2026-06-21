#include <string.h>
#include <stdlib.h>

#include "utils/config.h"

#define DEFAULT_PARTIDAS 50
#define DEFAULT_TEMPO 5.0
#define DEFAULT_VIZINHANCA 1000

void configurar_padrao(Config *cfg)
{

    cfg->partidas =
        DEFAULT_PARTIDAS;


    cfg->tempo_limite =
        DEFAULT_TEMPO;


    cfg->tamanho_vizinhanca =
        DEFAULT_VIZINHANCA;

}



void ler_parametros(
        int argc,
        char *argv[],
        Config *cfg)
{

    configurar_padrao(cfg);

    for(int i = 1; i < argc; i++)
    {

        if(strcmp(argv[i], "--partidas") == 0)
        {
            cfg->partidas =
                atoi(argv[++i]);
        }


        else if(strcmp(argv[i], "--tempo") == 0)
        {
            cfg->tempo_limite =
                atof(argv[++i]);
        }


        else if(strcmp(argv[i], "--vizinhanca") == 0)
        {
            cfg->tamanho_vizinhanca =
                atoi(argv[++i]);
        }

    }

}