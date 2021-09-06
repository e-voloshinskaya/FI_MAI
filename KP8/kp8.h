#ifndef kp8_h
#define kp8_h

#include "list.h"

void create(List* list);
bool does_list_exist(List* list);
void add_node(List* list, int pos, Item e);
void delete_node(List* list, int pos);
void print(List* list);
void swap_halves(List* list);

#endif 