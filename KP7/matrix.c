#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"


bool file_check(FILE* f)
{
    if (f == NULL) {
        printf("Error: File not found\n");
	return true;
    }

    fseek(f, 0, SEEK_END);
    long pos = ftell(f);
    if (pos ==  0) {
        printf("Error: File is empty\n");
	    return true;
    }
	
    seek(f, -2, SEEK_END);
    int c = getc(f);
    if (c >= '0' && c <= '9') {
        c = getc(f);
        if (c != 0x0a) {
            printf("Error: No new line at the end of the file\n");
            exit(1);
        }
    } else {
        printf("Error: Wrong file format. A new line may be needed at the end of the file\n");
        exit(1);
    }
    
    fseek(f, 0, SEEK_SET);
    return false;
}


FILE* file_read(const char* name)
{
    //printf("%s", name);
    FILE* f = fopen(name, "r");
    if (file_check(f)) {
        exit(1);
    }
    return f;
}


int find_size_matrix(FILE* f, int* n, int* m)
{
    int e = 0, elems = -1, nz_elems = 0, flag = 0, s;

    while (!feof(f)) {
        e = 0;
        int s = getc(f);
        if ((s < '0' || s > '9') && s != '-' && s != ' ' && s != '\n')
        {
            printf("Error: Input data should contain only integer numbers (positive without sign or negative)\n");
            exit(1);
        } else if (s == '-') {
            do {
                s = getc(f);
                if (s < '0' || s > '9') {
                    printf("Error: Input data should contain only integer numbers\n");
                    exit(1);
                }
                if ('0' < s && s <= '9')
                    flag = 1;
            } while (s != ' ' && s != '\n');
            s = ungetc(s, f);
            elems++;
            e++;
            if (flag == 1)
                nz_elems++;
            flag = 0;
        } else if (s == '\n') {
            (*n)++;
        } else
            ungetc(s, f);

        if (fscanf(f, "%d", &e))
        {
            if (e != 0)
                nz_elems++;
            
            elems++; // elems - общее количество чисел в файле
            //printf("(%d,%d,%d) ", e, elems, *n);
        } else {
            printf("Error: Input data should contain only integer numbers\n");
            exit(1);
        }
    }

    if (*n == 0 || elems <= 0 || elems % *n != 0) {
        printf("Error: The size of the matrix is incorrect or\n  the file contains excessive spaces\n");
        exit(1);

    *m = elems / *n;
    fseek(f, 0, SEEK_SET); // seek_set - начало файла, 0 - сдвиг (на 0 байтов)
    return nz_elems;
}


void enter_matrix(vector* plb, vector* pye, int n, int m, int N, FILE* f)
{
    int e = 0, pos = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            fscanf(f, "%d", &e);

            if (e != 0) {
                plb -> data[pos] = i * N + j;
                pye -> data[pos] = e;
                pos++;
            }
        }
    }
    plb -> data[pos] = -1;
}


void print_matrix(vector* plb, vector* pye, int n, int m, int N)
{
    int pos = 0, flag = 0, lambda, plb_i, plb_j;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
        {
            lambda = plb -> data[pos];
            if (lambda == -1) {
                flag = 1;
            }
            switch(flag) {
                case 0:
                    plb_i = lambda / N;  //3 строки можно заменить проверкой i* N + j == lambda
                    plb_j = lambda % N;
                    if (plb_i == i && plb_j == j) {
                        printf("%d ", pye -> data[pos]);
                        pos++;
                        break;
                    } //else {
                    //     printf("0 ");
                    // }
                    //break;
                case 1:
                    printf("0 ");
            }
        }
        printf("\n");
    }
    printf("\n");
}


void print_vector(vector* v, char* name)
{
    printf("%s: ", name);
    for (int i = 0; i < v -> size; i++)
    {
        printf("%d ", v -> data[i]);
    }
    printf("\n");
}

void print_as_stored(vector* plb, vector* pye)
{
    print_vector(plb, "LB");
    print_vector(pye, "YE");
    printf("\n");
}


void multiply_matrix(vector* plb, vector* pye, int n, int m, int N)
{
    //create and print row-vector
    int *row;
    row = (int*)malloc(n*sizeof(int));
    srand(time(NULL)); //генерируем разные значения для srand, чтобы получить разные случайные числа
    printf("row-v:\n");
    for (int i = 0; i < n; i++)
    {
        row[i] = -50 + rand()%100;
        printf("%d ", row[i]);
    }
    //print sp-matrix
    printf("\n\n  x\n\nsparse-matrix:\n");
    print_matrix(plb, pye, n, m, N);

    //creating res-vector and filling it by res of multiplication
    int *res;
    int e, i, j, lambda;
    res = (int*)malloc(m*sizeof(int));
    for (int p = 0; p < pye -> size; p++)
    {
        lambda = plb -> data[p]; // p = i * N + j
        i = lambda / N;
        j = lambda % N;
        e = pye -> data[p];
        res[j] += row[i] * e;
    }
    printf("  =\n\nresult:\n");

    //count non-zero in res and print
    int nz_res = 0;
    for (int p = 0; p < m; p++)
    {
        if (res[p] != 0)
            nz_res++;
        printf("%d ", res[p]);
    }
    printf("\n----------------------------------------------------\n");
    printf("| Number of non-zero elements in result vector: %2d |", nz_res);
    printf("\n----------------------------------------------------\n\n");
    
    // //rewrite matrix in usual form
    // int *matrix;
    // matrix = (int*)calloc(n*m, sizeof(int));
    // int lambda, i = 0, j = 0;
    // for (int p = 0; p < pye -> size; p++)
    // {
    //     lambda = plb -> data[p];
    //     i = lambda / N;
    //     j = lambda % N;
    //     matrix[i*N + j] = pye -> data[p];
    // }
    // //print matrix
    // for (int p = 0; p < n*m; p++)
    // {
    //     if (p % N == 0)
    //         if (p / N == n / 2)
    //             printf("   S = ");
    //         else
    //             printf("       ");
            
    //     printf("%d ", matrix[p]);
    //     if (p % N == m - 1)
    //         printf("\n");
    // }
    //free(matrix);
    //printf("\n=\n");
    
    free(row);
    free(res);
    
}
