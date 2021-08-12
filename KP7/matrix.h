#ifndef matrix_h
#define matrix_h
#include <stdbool.h>

#include "vector.h"

void find_size_matrix(FILE* f, int* n, int* m);
void enter_matrix(vector* pa, vector* pm, int n, int m, FILE* f);
void print_matrix(vector* pa, vector* pm, int n, int m);
void multiply_matrix(vector* pa, vector* pm, int n, int m);
bool is_file_empty(FILE* f);
FILE* file_read(const char*);

#endif