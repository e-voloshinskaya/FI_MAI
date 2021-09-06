#ifndef LIST_H
#define LIST_H
#include <stdbool.h>


/*
//элемент списка
typedef struct {
	float elem;
	Node *next;
} Node;
*/

// индексный доступ, без примен-я указателей и ссылок
typedef struct {
    int size;
    float *data;
} List;


void create_list(List* list, int sz);
int size_list(List* list);
void resize_list(List* list, int sz);
bool is_index_in_range(List* list, int i);
float* get_elem_list(List* list, int pos);
bool empty_list(List* list);
void destroy_list(List* list);

#endif
