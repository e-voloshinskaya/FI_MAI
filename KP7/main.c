#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "matrix.h"
#include "vector.h"


FILE* file_read(const char* name)
{
    //printf("%s", name);
    FILE* f = fopen(name, "r");
    if (file_check(f)) {
        exit(1);
    }
    return f;
}


bool file_check(FILE* f)
{
    if (f == NULL) {
        printf("File not found\n");
	return true;
    }

    fseek(f, 0, SEEK_END);
    long pos = ftell(f);
    if (pos ==  0) {
        printf("File is empty\n");
	return true;
    }
    fseek(f, 0, SEEK_SET);

    return false;
}


int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Exactly one argument is required. Enter filename:\n");
        exit(1);
    }

    FILE* f = file_read(argv[1]);

    int n = 0, m = 0;
    find_size_matrix(f, &n, &m);
    printf("n = %d  m = %d\n", n, m);

    return 0;
}