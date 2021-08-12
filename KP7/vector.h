#ifndef vector_h
#define vector_h
#include <stdbool.h>

typedef struct
{
    int size;
    int* data;
} vector;

void create_vector (vector* v, int sz); //!!!!!!!!!!!!!!!!
bool empty_vector (vector* v);
int size_vector (vector* v);
void resize_vector (vector* v, int sz);
bool equal_vector (vector* l, vector* r);
void destroy_vector (vector* v);

#endif