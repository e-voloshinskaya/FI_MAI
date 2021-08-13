#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "matrix.h"
#include "vector.h"


void menu()
{
        printf("Available options:\n");
        printf("1. Print matrix in usual form\n");
        printf("2. Print matrix as stored\n");
        printf("3. Multiply the row vector by the entered sparse matrix and calculate the number of non-zero elements of the result\n");
        printf("4. Quit\n");
}


int main(int argc, char const *argv[])
{
    //reading filename from command line
    if (argc != 2) {
        printf("Error: Exactly one argument is required. Enter filename:\n");
        exit(1);
    }

    //preprocessing file
    FILE* f = file_read(argv[1]);
    int n = 0, m = 0, nz = 0;
    nz = find_size_matrix(f, &n, &m);
    printf("Input file is correct. Matrix size: n = %d rows and m = %d columns, %d non-zero elements\n\n", n, m, nz);

    //creating vectors
    vector LB, YE;
    vector *plb = &LB, *pye = &YE;
    create_vector(plb, nz + 1);
    create_vector(pye, nz);

    //for reading: using max of row, column to have a bijection between matrices in file and in program
    int N = n;
    if (n < m)
        N = m;
    //reading matrix
    enter_matrix(plb, pye, n, m, N, f);

    //user interface
    while (true) {
        int opt = 0;

        menu();
        printf("Choose option 1-4:\n");
        if (scanf("%d", &opt) != 1) {
            printf("Error: There is no such option\n");
            scanf("%*[^\n]"); //stream cleaning
            continue;
        }
        printf("\n");
        switch (opt) {
            case 1:
                print_matrix(plb, pye, n, m, N);
                break;
            case 2:
                print_as_stored(plb, pye, n, m);
                break;
            case 3:
                multiply_matrix(plb, pye, n, m, N);
                break;
            case 4:
                exit(0);
        }
    }
    free(plb);
    free(pye);
    fclose(f);
    return 0;
}
