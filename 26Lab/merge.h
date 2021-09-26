#ifndef merge_h
#define merge_h

#include "queue.h"


extern void queue_merge(queue* const result,
                        queue* const left, queue* const right);
extern void queue_sort(queue* const q);

#endif