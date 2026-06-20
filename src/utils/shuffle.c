#include "shuffle.h"
#include <stdlib.h>
#include <string.h>

// Fisher–Yates
void shuffle(void *array, int n, size_t size)
{
    char *arr = (char *)array;


    for(int i = n - 1; i > 0; i--)
    {

        int j = rand() % (i + 1);

        char temp[size];

        memcpy(temp,
               arr + i * size,
               size);


        memcpy(arr + i * size,
               arr + j * size,
               size);


        memcpy(arr + j * size,
               temp,
               size);
    }
}