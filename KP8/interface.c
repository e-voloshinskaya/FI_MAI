#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "kp8.h"


void menu()
{
        printf("Available options:\n");
        printf("a - Add a node to the list\n");
        printf("d - Delete a node \n");
        printf("p - Print the list\n");
        printf("l - Print list length\n");
        printf("s - Swap the halves of the list\n");
        printf("q - Quit\n");
}

int main()
{
    List* l = NULL;
    create(l);
    int pos;

    for(;;)
    {
        menu();
        char c = getchar();
        if (c == '\n' && c == ' ')
            continue;
        switch (c) {
        case 'a':
            printf("Enter the item you want to add: ");
//!!!! небезопасный ввод!
            Item elem = 0;
            scanf("%f", &elem);
            print(l);
            printf("Enter the index (from 1 to length of list), where to put an item");
            scanf("%d", &pos);
            if (is_index_in_range(l, pos - 1) && does_list_exist(l))
                add_node(l, pos - 1, elem);
            break;
        case 'p':
            if (does_list_exist(l))
                print(l);
            break;
        case 's':
            if (does_list_exist(l))
                swap_halves(l);
        case 'l':
            if (does_list_exist(l))
                printf("List length = %d", size_list(l));
            break;
        case 'd':
//!!!! небезопасный ввод!
            print(l);
            printf("Enter the index of the item you want to delete (from 1 to length of list)");
            scanf("%d", &pos);
            if (is_index_in_range(l, pos - 1) && does_list_exist(l))
                delete_node(l, pos - 1);
            break;
        case 'q':
            destroy_list(l);
            exit(0);
        default:
            printf("There is no such option. Try again.\n");
            break;
        }
        
    }
    return 0;
}
