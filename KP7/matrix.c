#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"


bool file_check(FILE* f)
{
    if (f == NULL) {
        printf("Error: File not found\n");
	return true;
    }

    fseek(f, 0, SEEK_END);
    long pos = ftell(f);
    if (pos ==  0) {
        printf("Error: File is empty\n");
	    return true;
    }
    
    fseek(f, 0, SEEK_SET);
    return false;
}


FILE* file_read(const char* name)
{
    //printf("%s", name);
    FILE* f = fopen(name, "r");
    if (file_check(f)) {
        exit(1);
    }
    return f;
}


int find_size_matrix(FILE* f, int* n, int* m)
{
    int e = 0, elems = -1, nz_elems = 0, s;

    while (!feof(f)) {
        e = 0;
        int s = getc(f);
        if (s == '\n')
            (*n)++;
        else
            ungetc(s, f);

        if (fscanf(f, "%d", &e))
        {
            if (e != 0)
                nz_elems++;
            
            elems++; // elems - общее количество чисел в файле
            printf("(%d,%d,%d) ", e, elems, *n);
        } else {
            printf("Error: Input data should contain only numbers\n");
            exit(1);
        }
    }

    if (*n == 0 || elems <= 0 || elems % *n != 0 || e != 0) {
        printf("Error: The size of the matrix is incorrect or\n  there is no new line at the end of the file\n");
        exit(1);
    }

    *m = elems / *n;
    fseek(f, 0, SEEK_SET); // seek_set - начало файла, 0 - сдвиг (на 0 байтов)
    return nz_elems;
}


void enter_matrix(vector* plb, vector* pye, int n, int m, FILE* f)
{
    int e = 0, pos = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            fscanf(f, "%d", &e);

            if (e != 0) {
                plb -> data[pos] = i*n + j;
                pye -> data[pos] = e;
                pos++;
            }
        }
    }
    plb -> data[pos] = -1;
}
