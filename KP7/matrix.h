#ifndef func_h
#define func_h

#include "vector.h"

void find_size_matrix(FILE* f, int* n, int* m);
void enter_matrix(vector* pa, vector* pm, int n, int m, FILE* f);
void print_matrix(vector* pa, vector* pm, int n, int m);
void multiply_matrix(vector* pa, vector* pm, int n, int m);
char is_file_empty(FILE* f);
FILE* file_read();

#endif