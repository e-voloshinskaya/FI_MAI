#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "table.h"

void read_data(char* data, Table* l) {
    char* elem = strtok(data, " +-i"); // разбиение строки по указ. разделителю
    long long tempReal = strtoll(elem, NULL, 10); // конвертирование строки в long long
    elem = strtok(NULL, " i");
    char* temp = strtok (NULL, " i");
    long long tempImg;
    if (temp) {
        strcat(elem, temp); // добавить в конец строки
        tempImg = strtoll(elem, NULL, 10);
        elem = strtok(NULL, "");
    }
    else
        tempImg = 0;
    char string[100];
    strcpy(string, elem); // оставшиеся после считывания числа символы записываем в data
    Item toList;
    toList.key.real = tempReal;
    toList.key.img = tempImg;
    strcpy(toList.data, string);
    iterator last = Last(l);
    Insert(l, &last, toList);
}

void menu()
{
    printf("Available options:\n");
    printf("s - Get size of the table\n");
    printf("p - Print the table\n");
    printf("i - Simple insertion sort\n");
    printf("b - Search binary\n");
    printf("q - Quit\n");
}

int main(int argc, char *argv[]) {
    Table l;
    Create(&l);

    FILE *fp;
    char tempo[100];

    if ((fp = fopen(argv[1], "r"))==NULL) {
        printf("Cannot open the file\n");
        exit(1);
    }
    //MAX DATA ARRAY SIZE = 100
    while(!feof(fp)) {
        if (fgets(tempo, 100, fp)) {
            read_data(tempo, &l);
        }
    }
    //exit(0);
    char c;
    bool sorted = false;
    menu();
    while ((c = getchar()) != EOF) {
        switch(c) {
            case 's': {
                printf("Size = %d\n\n", size(&l));
                break;
            }
            case 'p': {
                if (!sorted)
                    printf("~unsorted~\n\n");
                else printf("~sorted~\n\n");
                iterator first = First(&l);
                iterator last = Last(&l);
                while(!Equals(&first, &last)) {
                    Item elem = Read(&first);
                    printf("key: %lld+i*(%lld)   data: %s\n", elem.key.real, elem.key.img, elem.data);
                    Next(&first);
                }
                printf("\n\n");
                break;

            }
            case 'i': {
                if (sorted) {
                    printf("Already sorted\n\n");
                    break;
                }
                insertionSort(&l);
                sorted = true;
                break;
            }
            case 'b': {
                getchar();
                if (!sorted) {
                    printf("Sort required\n\n");
                    break;
                }
                complex key;
                printf("Enter:\n1) real part of the key\n2) key imaginary part\n");
                scanf("%lld %lld", &key.real, &key.img);
                iterator first = First(&l);
                iterator last = Last(&l);
                iterator found = binSearch(&l, first, last, key);
                Item elem = Read(&found);
                if (elem.key.real == key.real && elem.key.img == key.img)
                    printf("FOUND BINARY:\n key: %lld+i*(%lld)  data: %s\n", elem.key.real, elem.key.img, elem.data);
                else printf("Not in table\n\n");
                break;
            }
            case 'q':
                Destroy(&l);
                exit(0);
                break;
            case 'h':
                menu();
                break;
            case '\n':
                menu();
                break;
            default:
                printf("There is no such option. To see options enter 'h'\n\n");
                break;
        }
    }
}