#ifndef SHUFFLE_H
#define SHUFFLE_H

/*
    Fisher-Yates shuffle genérico

    array  -> ponteiro para o primeiro elemento
    n      -> quantidade de elementos
    size   -> tamanho de cada elemento em bytes

    Exemplo:
        shuffle(vetor, n, sizeof(int));
*/

void shuffle(void *array, int n, size_t size);


#endif