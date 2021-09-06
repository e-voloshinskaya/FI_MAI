#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "list.h"

const Item barrier = FLT_MAX;

void create_list(List* list, int sz)
{
    list -> size = sz;
    list -> data = (Item*)malloc(list -> size * sizeof(Item));
    list -> data[0] = barrier;
}

void resize_list(List* list, int sz)
{
    list -> size = sz;
    list -> data = realloc(list -> data, sizeof(Item) * list -> size);
}

int size_list(List* list)
{
    return list -> size;
}

bool is_index_in_range(List* list, int i)
{
    if (i >= 0 && i < size_list(list))
        return true;
    else {
        printf("Index out of range\n");
        return false;
    }
}

Item* get_elem_list(List* list, int pos)
{
    if (is_index_in_range(list, pos)) {
        return &(list -> data[pos]); //передаем ссылку на расположение элемента
    }
}

bool empty_list(List* list)
{
    return (list -> size == 0) ? true : false;
}

void destroy_list(List* list)
{
    list -> size = 0;
    free(list -> data);
}
