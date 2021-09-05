#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "list.h"

const Item barrier = FLT_MAX;

void create_list(List* list, int sz)
{
    list -> size = sz;
    list -> data = (Item*)malloc(list -> size, sizeof(Item));
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

Item* get_elem_list(List* list, int pos)
{
    if (is_index_less_size(list, pos)) {
        return &(list -> data[pos]); //??????? передаем ссылку на расположение элемента
    } else {
        printf("Wrong index\n"); // только принт?
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