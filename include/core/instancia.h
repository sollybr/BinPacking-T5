#ifndef INSTANCIA_H
#define INSTANCIA_H

typedef struct {
    int n;          // n objetos
    int capacidade; // capacidade bin
    int *pesos;     // pesos objetos
} Instancia;

Instancia* ler_instancia(const char *arquivo);

void liberar_instancia(Instancia *inst);

#endif