#include <stdio.h>
#include <stdlib.h>


void menu()
{
        printf("Available options:\n");
        printf("a - Add a node to the list\n");
        printf("d - Delete the node\n");
        printf("p - Print the list\n");
        printf("s - Swap the halves of the list\n");
        printf("q - Quit\n");
}

int main()
{
    LIST* l = NULL;
    create(l);

    add_node(l, 0);
    print(l);
    


    //!!!!!!!!!!!!!!!!!! передаем индекс не позицию
    int idx = pos - 1;
    return 0;
}
