#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "struct.h"

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Exactly one argument is required\n");
        exit(1);
    }
    if (argv[1][0] == 'w') {

        // if (argc != 2) {
        //     fprintf(stderr, "Exactly one argument is required\n");
        //     exit(1);
        // }

        printf("%s\n", argv[1]);
        write_file();

    } else if (argv[1][0] == 'r') {

        // if (argc != 2) {
        //     fprintf(stderr, "Exactly one argument is required\n");
        //     exit(1);
        // }
        read_file();

    } else if(argv[1][0] == 'p') {

        count_scholars();
    }

    return 0;
}
