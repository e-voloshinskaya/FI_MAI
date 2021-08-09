#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

void find_size_matrix(FILE* f, int* n, int* m)
{
    int a = 0;
    
    while (!feof(f)) {
        if (fgetc(f) == '\n')
            *n += 1;
        if (fscanf(f, "%d", &a))
            *m +=1;
    }
    *m /= *n; 
    if (*m % *n != 0)
        perror("Input data is not a matrix");

    fseek(f, 0, SEEK_SET);
// seek_set - начало файла, 0 - сдвиг (на 0 байтов)
}

