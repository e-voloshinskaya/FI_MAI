#include <stdio.h>
#include <stdlib.h>

#include "list.h"


void create(List* list)
{
    create_list(list, 1);
}

bool does_list_exist(List* list)
{
    if (list == NULL) {
        printf("List doesn't exist.\n\n");
        return false;
    } else {
        return true;
    }
}


void add_node(List* list, int pos, float e)
{
    resize_list(list, size_list(list) + 1);
    //printf("List length = %d\n\n", size_list(list));
    for (int i = size_list(list) - 1; i > pos; --i)
    {
        //printf("List length = %d\n\n", size_list(list));
	    //printf("%d, %d\n", pos, i);
        *get_elem_list(list, i) = *get_elem_list(list, i - 1);
    }
    *get_elem_list(list, pos) = e;
}

void delete_node(List* list, int pos)
{
    for (int i = pos; i < size_list(list) - 1; i++)
    {
        *get_elem_list(list, i) = *get_elem_list(list, i + 1); //элемент (значение) по адресу i изменяем на элемент по адресу i+1
    }
    resize_list(list, size_list(list) - 1);
    
}

void print(List* list)
{
    printf("List elements:\n");
    if (empty_list(list))
        printf("  *List is empty*\n");
    else {
        for (int i = 0; i < size_list(list) - 1; i++)
        //for (int i = 0; i < size_list(list); i++) // печатаем барьерный элемент
        {
            printf("%f ", *get_elem_list(list, i));
        }
        printf("\n");
    }
    printf("\n");
}

/*
void destroy(List* list)
{
    does_list_exist(list);
    destroy_list(list);
}
void size(List* list)
{
    does_list_exist(list);
    printf("%d\n", size_list(list));
}
*/

void swap_halves(List* list)
{
    if ((size_list(list) - 1) % 2 == 0)
    {
        int half = (size_list(list) - 1) / 2;
        for (int i = 0; i < half; i++)
        {
            float n = *get_elem_list(list, i);
	    //printf("%float", n);
            *get_elem_list(list, i) = *get_elem_list(list, half + i);
            *get_elem_list(list, half + i) = n;
        }
        print(list);
    } else {
        printf("List has an odd number of elements. Add or delete one to swap halves.\n\n");
    }
}