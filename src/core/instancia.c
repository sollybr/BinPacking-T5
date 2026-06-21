#include <stdio.h>
#include <stdlib.h>
#include "core/instancia.h"


Instancia* ler_instancia(const char *arquivo)
{
    FILE *fp = fopen(arquivo, "r");

    if(fp == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return NULL;
    }


    Instancia *inst = malloc(sizeof(Instancia));


    if(inst == NULL)
    {
        fclose(fp);
        return NULL;
    }


    // primeira linha: n
    fscanf(fp, "%d", &inst->n);


    // segunda linha: capacidade
    fscanf(fp, "%d", &inst->capacidade);

    inst->pesos = malloc(sizeof(int) * inst->n);


    if(inst->pesos == NULL)
    {
        fclose(fp);
        free(inst);
        return NULL;
    }

    for(int i = 0; i < inst->n; i++)
    {
        fscanf(fp, "%d", &inst->pesos[i]);
    }

    fclose(fp);


    return inst;
}



void liberar_instancia(Instancia *inst)
{
    if(inst == NULL)
        return;


    free(inst->pesos);

    free(inst);
}