#ifndef matrix_h
#define matrix_h
#include <stdbool.h>

#include "vector.h"

bool file_check(FILE* f);
FILE* file_read(const char*);
int find_size_matrix(FILE* f, int* n, int* m);
void enter_matrix(vector* plb, vector* pye, int n, int m, FILE* f);
void print_matrix(vector* plb, vector* pye, int n, int m);
void multiply_matrix(vector* plb, vector* pye, int n, int m);

#endif