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

        write_file();

    } else if (argv[1][0] == 'r') {

        read_file();

    } else if(argv[1][0] == 'p') {

        count_scholars();
    }

    return 0;
}
