#ifndef queue_h
#define queue_h


typedef struct Item
{
    int data;
    struct Item *next;
} Item;

typedef struct
{
    Item* first;
    Item* last;
    int size;
} queue;


void init(queue* q);
int empty(const queue* q);
int size(const queue* q);
int push (queue* q, const int t);
int pop(queue* q);
int *top(const queue* q);
void destroy(queue* q);
void print(queue* q);
void queue_sort(queue* const q);

#endif