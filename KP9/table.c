#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "table.h"

bool Equals(const iterator* lhs, const iterator* rhs) {
    return lhs->node == rhs->node;
}

void Next(iterator* i) {
    i->node = i->node->next;
}

void Prev(iterator* i) {
    i->node = i->node->prev;
}

Item Read(const iterator* i) {
    return i->node->item;
}

void Create(Table* l) {
    l->head = (Node*) malloc(sizeof(Node));
    l->head->next = l->head->prev = l->head;
    l->size = 0;
}

iterator First(const Table* l) {
    iterator i = {l->head->next};
    return i;
}

iterator Last(const Table* l) {
    iterator i = {l->head};
    return i;
}

bool isEmpty(const Table* l) {
    iterator lhs = First(l);
    iterator rhs = Last(l);
    return Equals(&lhs, &rhs);
}

int size(const Table* l) {
    return l->size;
}

iterator Insert(Table* l, iterator* i, Item elem) { //insert _before_ node with iterator i
    iterator new_i = {malloc(sizeof(Node))};
    if (!new_i.node)
        return Last(l);
    new_i.node->item = elem;
    new_i.node->next = i->node;
    new_i.node->prev = i->node->prev;
    new_i.node->prev->next = new_i.node;
    i->node->prev = new_i.node;
    l->size++;
    return new_i;
}

iterator Delete(Table* l, iterator* i) {
    iterator tmp = Last(l);
    if(Equals(i, &tmp))
        return tmp;
    tmp.node = i->node->next;
    tmp.node->prev = i->node->prev;
    i->node->prev->next = tmp.node;
    l->size--;
    i->node = NULL;
    free(i->node);
    return tmp;
}

void Destroy(Table* l) {
    Node* i = l->head->next;
    while(i != l->head) {
        Node* current = l->head;
        i = i->next;
        free(current);
    }
    l->head = NULL;
    free(l->head);
    l->size = 0;
}

bool cmp(complex* lhs, complex* rhs) {
    long long lval = lhs->real * lhs->real + lhs->img * lhs->img;
    long long rval = rhs->real * rhs->real + rhs->img * rhs->img;
    return lval > rval;
}

bool cmp2(complex* lhs, complex* rhs) {
    long long lval = lhs->real * lhs->real + lhs->img * lhs->img;
    long long rval = rhs->real * rhs->real + rhs->img * rhs->img;
    return lval >= rval;
}

int distance(iterator lhs, iterator rhs) {
    int cnt = 0;
    while (!Equals(&lhs, &rhs)) {
        Next(&lhs);
        cnt++;
    }
    return cnt;
}

iterator nPos(const Table* l, int n) {
    iterator iterator = First(l);
    for (int i = 0; i < n; i++) {
        Next(&iterator);
    }
    return iterator;
}

iterator binSearch(Table* l, iterator lhs, iterator rhs, complex value) {
    //Prev(&rhs);
    iterator first = First(l);
    while (distance(lhs, rhs) > 1) {
        int m = (distance(first, lhs) + distance(first, rhs)) / 2;
        iterator mid = nPos(l, m);
        complex key = Read(&mid).key;
        if (cmp2(&value, &key)) {
            lhs = mid;
        }
        else rhs = mid;
    }
    return lhs;
}

void sortInsert(Table* l, Item unit) {
    iterator first = First(l);
    iterator last = Last(l);
    //Next(&first);
    while (!Equals(&first, &last)) {
        Item cmpUnit = Read(&first);
        if (!cmp(&unit.key, &cmpUnit.key)) {
            Insert(l, &first, unit);
            return;
        }
        Next(&first);
    }
    Insert(l, &last, unit);
}

void insertionSort(Table* l) {
    bool unsorted = true;
    while (unsorted) {
        unsorted = false;
        iterator first = First(l);
        iterator last = Last(l);
        Prev(&last);
        while (!Equals(&first, &last)) {
            complex lhs = Read(&first).key;
            Next(&first);
            complex rhs = Read(&first).key;
            if (cmp(&lhs, &rhs)) {
                unsorted = true;
                Item unit = Read(&first);
                Delete(l, &first);
                sortInsert(l, unit);
                break;
            }
        }
    }
}
