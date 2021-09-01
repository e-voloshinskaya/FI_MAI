#include <stdio.h>
#include <stdlib.h>

#include "list.h"


void create(List* list)
{
    create_list(list, 0);
}

void does_list_exist(List* list)
{
    if (list == NULL) {
        printf("List doesn't exist\n");
        //exit?
    } else {
        //exit(1);return?
    }
}

//!!!!!!!!!!!!!! доделать!!!!!!!
void add_node(List* list, int pos)
{
    does_list_exist(list); // убрать эту строку куда-нибудь в интерфейс чтобы не повторялась
    resize_list(list, size_list(list) + 1);

}

bool is_index_less_size(List* list, int i)
{
    if (i >= 0 && i < size_list(list))
        return true;
    return false;

}

void delete_node(List* list, int pos)
{
    does_list_exist(list);
    for (int i = pos; i < size_list(list); i++)
    {
        *get_elem_list(list, i) = *get_elem_list(list, i + 1); //элемент по адресу i меняем на элемент по адресу i+1
    }
    resize_list(list, size_list(list) - 1);
    
}

void print(List* list)
{
    does_list_exist(list);
    for (int i = 0; i < size_list(list); i++)
    {
        printf("%f ", get_elem_list(list, i));
    }
    printf("\n");
}

/*
void destroy(List* list)
{
    does_list_exist(list);
    destroy_list(list);
}
*/
void size(List* list)
{
    does_list_exist(list);
    printf("%d\n", size_list(list));
}