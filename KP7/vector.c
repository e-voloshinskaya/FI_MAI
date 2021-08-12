#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vector.h"

//объявляем длину и заполняем нулями
void create_vector(vector* v, int sz)
{
    v -> size = sz;
    v -> data = (int*)calloc(v -> size, sizeof(int));
    // v -> data = (int*)malloc(sizeof(int) * v -> size);
    // for (int i = 0; i < sz; i++) {
    //     v -> data[i] = 0;
    // }
}

bool empty_vector(vector* v)
{
    return (v -> size == 0);
}

int size_vector(vector* v)
{
    return v -> size;
}

void resize_vector(vector* v, int sz)
{
    v -> size = sz;
    v -> data = realloc(v -> data, sizeof(int) * v -> size);
}

bool equal_vector(vector* l, vector* r)
{
    if (l -> size != r -> size) 
        return false;
    for (int i = 0; i < l -> size; i++)
        if (l -> data[i] != r -> data[i])
            return false;
    return true;
}

void destroy_vector(vector* v)
{
    v -> size = 0;
    free(v -> data);
}