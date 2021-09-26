#include "queue.h"
#include "merge.h"


void queue_merge(queue* const result,
                queue* const left, queue* const right)
    {
        queue *tmp;
        init(tmp);

        while(!empty(left) && !empty(right)) {
            if (*top(left) < *top(right))
                push(tmp, pop(left));
            else
                push(tmp, pop(right));
        }

        while (!empty(left))
            push(tmp, pop(left));

        while (!empty(right))
            push(tmp, pop(right));

        while (!empty(tmp))
            push(result, pop(tmp));

        destroy(tmp);
    }


void queue_sort(queue* const q)
{
    queue *left;
    queue *right;
    init(left);
    init(right);
    while (!empty(q)) {
        if (size(q) % 2 == 0)
            push(left, pop(q));
        else
            push(right, pop(q));
    }

    if (size(left) > 1)
        queue_sort(left);

    if (size(right) > 1)
        queue_sort(right);

    queue_merge(q, left, right);

    destroy(right);
    destroy(left);
}
