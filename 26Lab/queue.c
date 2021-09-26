#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void init(queue* q) // создаем терминатор
{
    q->first = q->last = malloc(sizeof(Item)); // !должна быть ссылка на 1 и ту же память
    q->size = 0;
}

int empty(const queue* q)
{
    return q->size == 0;
}

int size(const queue* q)
{
    return q -> size;
}

int push(queue* q, const int t)
{
    if(!(q->last->next = malloc(sizeof(Item))))
        return 0;
    q->last->data = t;
    q->last = q->last->next;
    q->size++;
    return 1;
}

int pop(queue* q)
{
    if(empty(q))
        return 0;
    Item* pi = q->first;
    int top = pi->data;
    q->first = q->first->next;
    q->size--;
    free(pi);
    return top;
}


int* top(const queue* q)
{
    if(!empty(q))
        return &(q->first->data);
    return 0;
}

void destroy(queue* q)
{
    q->last->next = NULL;
    Item* pi = q->first;
    q->first = q->first->next;
    free(pi);
    if(q->first)
        destroy(q);
    q->last = NULL;
    q->size = 0;
}

void print(queue* q)
{
    if(!empty(q)) {
        Item* curr = q->first;
        printf("Queue: ");
        for(int i = 0; i < q->size; i++)
        {
            printf("%d ", curr->data);
            curr = curr->next;
        }
        printf("\n\n");
    }
    else 
    {
        printf("Queue is empty\n\n");
    }
}

static void queue_merge(queue* const result,
                queue* const left, queue* const right)
    {
        queue tmp = { 0 };
        init(&tmp);

        while(!empty(left) && !empty(right)) {
            if (*top(left) < *top(right))
                push(&tmp, pop(left));
            else
                push(&tmp, pop(right));
        }

        while (!empty(left))
            push(&tmp, pop(left));

        while (!empty(right))
            push(&tmp, pop(right));

        while (!empty(&tmp))
            push(result, pop(&tmp));

        destroy(&tmp);
    }


void queue_sort(queue* const q)
{
    queue left = { 0 };
    queue right = { 0 };
    init(&left);
    init(&right);
    
    while (!empty(q)) {
        if (size(q) % 2 == 0)
            push(&left, pop(q));
        else
            push(&right, pop(q));
    }

    if (size(&left) > 1)
        queue_sort(&left);

    if (size(&right) > 1)
        queue_sort(&right);

    queue_merge(q, &left, &right);

    destroy(&right);
    destroy(&left);
}