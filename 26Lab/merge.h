#ifndef merge_h
#define merge_h

#include "queue.h"


void queue_merge(queue* const result,
                        queue* const left, queue* const right);
void queue_sort(queue* const q);
void merge_2();

#endif