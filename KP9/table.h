#ifndef TABLE_H
#define TABLE_H

#include <stdbool.h>

typedef struct complex_ {
    long long real;
    long long img;
} complex;

typedef struct Item_ {
    complex key;
    char data[100];
} Item;

typedef struct Node_ {
    Item item;
    struct Node_* prev;
    struct Node_* next;
} Node;

typedef struct Table_ {
    Node* head;
    int size;
} Table;

typedef struct iterator_ {
    Node* node;
} iterator;


bool Equals(const iterator* lhs, const iterator* rhs);
void Next(iterator* i);
void Prev(iterator* i);
Item Read(const iterator* i);
void Write(const iterator* i, Item elem);
void Create(Table* l);
iterator First(const Table* l);
iterator Last(const Table* l);
bool isEmpty(const Table* l);
int size(const Table* l);
iterator Insert(Table* l, iterator* i, Item elem);
iterator Delete(Table* l, iterator* i);
void Destroy(Table* l);
int distance(iterator lhs, iterator rhs);
iterator binSearch(Table* l, iterator lhs, iterator rhs, complex value);
void insertionSort(Table* l);

#endif
