#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"


void find_size_matrix(FILE* f, int* n, int* m)
{
    int e = 0, elems = 0, tmp = 0;

    while (!feof(f)) {
        e = tmp;
        tmp = 0;
        if (fgetc(f) == '\n')
            *n += 1;
        if (fscanf(f, "%d", &tmp))
        {
            elems +=1; // elems - общее количество чисел в файле
            //printf("(%d,%d,%d,%d) ", e, tmp, elems, *n);
        } else {
            printf("Error: Input data should contain only numbers\n");
            exit(1);
        }
    }

    if (*n == 0 || elems == 1 || elems % *n != 0 || tmp != 0) {
        printf("Error: The size of the matrix is incorrect or\n  there is no new line at the end of the file\n");
        exit(1);
    }

    *m = elems / *n;
    fseek(f, 0, SEEK_SET);
// seek_set - начало файла, 0 - сдвиг (на 0 байтов)
}
