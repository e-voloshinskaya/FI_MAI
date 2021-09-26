#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "merge.h"

void menu()
{
        printf("Available options:\n");
        printf("1. Push element to the tail of the queue\n");
        printf("2. Pop first element of the queue\n");
        printf("3. Get first element of the queue\n");
        printf("4. Print size of the queue\n");
        printf("5. Print the queue\n");
        printf("6. Sort the queue\n");
        printf("7. Quit\n");
}

int main()
{
	queue *q;
	init(q);
    while (1) {
        int opt = 0;

        menu();
        printf("Choose option 1-7:\n");
        if (scanf("%d", &opt) != 1 || opt < 1 || opt > 7) {
            printf("Error: There is no such option\n\n");
            scanf("%*[^\n]"); //stream cleaning
            continue;
        }
        printf("\n");
        switch (opt) {
            case 1:
                printf("Enter an element:\n");
                int e;
                scanf("%d", &e);
                push(q, e);
                break;

            case 2:
                if (!pop(q))
                    printf("Error. The queue is empty\n\n");
                else
                    printf("Completed successfully\n\n");
                break;

            case 3:
                if (empty(q))
                    printf("Error. The queue is empty\n\n");
                else
                    printf("First element: %d\n\n", *top(q));
                break;

            case 4:
                printf("Size of the queue: %d\n\n", size(q));
                break;

            case 5:
                print(q);
                break;

            case 6:
                queue_sort(q);
                break;

            case 7:
                exit(0);
        }
    }

    destroy(q);
	return 0;
}