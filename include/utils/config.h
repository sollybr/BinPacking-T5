#ifndef CONFIG_H
#define CONFIG_H


typedef struct {

    int partidas;

    double tempo_limite;

    int tamanho_vizinhanca;


} Config;


void configurar_padrao(Config *cfg);


void ler_parametros(
    int argc,
    char *argv[],
    Config *cfg
);


#endif