#include <stdio.h>
#include <stdlib.h>

#include "list.h"


void create(List* list)
{
    create_list(list, 1);
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
void add_node(List* list, int pos, Item e) //pos = индекс эл в векторе + 1
{
    does_list_exist(list); // убрать эту строку куда-нибудь в интерфейс чтобы не повторялась
    resize_list(list, size_list(list) + 1);
    for (int i = size_list(list) - 1; i > pos; i--)
    {
        //list -> data[pos] = list -> data[pos - 1];
        *get_elem_list(list, pos) = *get_elem_list(list, pos - 1);
    }
    *get_elem_list(list, pos) = e;
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
        *get_elem_list(list, i) = *get_elem_list(list, i + 1); //элемент (значение) по адресу i изменяем на элемент по адресу i+1
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

void swap_halves(List* list)
{
    if ((size_list(list) - 1) % 2 == 0)
    {
        half = (size_list(list) - 1) / 2;
        for (int i = 0; i < half - 1; i++)
        {
            Item n = *get_elem_list(list, i);
            *get_elem_list(list, i) = *get_elem_list(list, half);
            *get_elem_list(list, half) = n;
        }
        print(list);
    } else {
        printf("List has odd number of elements. Add or delete one to swap halves.")
    }
}
