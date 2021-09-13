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
    List* pl = NULL; // created empty pointer on list
    List l; // created list
    pl = &l;
    create(pl);
    int idx;

    for(;;)
    {
        menu();
        //scanf("%*[^\n]");
        printf("Choose option:\n");
        char c = getchar();
        //getchar();
        //scanf("%*[^\n]");
        if (c == '\n' || c == ' ')
            c = getchar();
        //printf("%d\n", c);
        printf("\n");
        switch (c) {
            case 'a':
                if (does_list_exist(pl))
                {
                    printf("Enter the item you want to add: ");
        //!!!! небезопасный ввод!
                    float elem = 0;
                    scanf("%f", &elem);
                    printf("\n");
                    print(pl);
                    printf("Enter the index (from 1 to length of list), where to put an item: ");
                    scanf("%d", &idx);
                    if (is_index_in_range(pl, idx - 1) && does_list_exist(pl))
                    {
                        add_node(pl, idx - 1, elem);
                        printf("\n");
                    }
            //scanf("%*[^\n]");
                }
                break;
            case 'p':
                if (does_list_exist(pl))
                    print(pl);
                break;
            case 's':
                if (does_list_exist(pl))
                    swap_halves(pl);
                break;
            case 'l':
                if (does_list_exist(pl))
                    printf("List length = %d\n\n", size_list(pl) - 1); //excluding barrier elem
                break;
            case 'd':
    //!!!! небезопасный ввод!
                if (does_list_exist(pl))
                {
                    print(pl);
                    printf("Enter the index of the item you want to delete (from 1 to length of list): ");
                    scanf("%d", &idx);
                    if (idx == size_list(pl))
                        printf("Index out of range.\n\n");
                    else if (is_index_in_range(pl, idx - 1) && does_list_exist(pl))
                    {
                        delete_node(pl, idx - 1);
                        printf("\n");
                    }
                }
                break;
            case 'q':
                if (does_list_exist(pl))
                    destroy_list(pl);
                exit(0);
                break;
            default:
                printf("There is no such option. Try again.\n\n");
                break;
        }
        
    }
    free(pl);
    return 0;
}