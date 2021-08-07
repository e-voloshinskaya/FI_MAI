#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"

student students[students_length];


void check_file_existence(FILE *file)
{
    if (file == NULL) {
        fprintf(stderr, "Error. Can't open file\n");
        exit(1);
    }
}

void write_file()
{
    FILE *f = fopen("marks.bin", "wb");
    fwrite(&MAI_students, sizeof(student), students_length, f);
    /*for (int i = 0; i < students_length; i++)
    {
        fwrite(&MAI_students[i], sizeof(student), 1, f);
    }*/
    fclose(f);
}


void print_file(student array[])
{
    printf("-----------------------------------------------------------------------------------------------------------\n");
    printf("|    surname    | initials | gender | group | calculus | linear algebra | programming | english | history |\n");
    printf("-----------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < students_length; i++)
    {
        /*
        printf("|%15s|     %s|       %s|%s|%10d|%16d|%13d|%9d|%9d|\n",
            array[i].surname,
            array[i].initials[0], array[i].initials[1], array[i].initials[2], array[i].initials[3], array[i].initials[4],
            array[i].gender[0],
            array[i].group[0], array[i].group[1], array[i].group[2], array[i].group[3], array[i].group[4], array[i].group[5], array[i].group[6],
            array[i].calculus,
            array[i].linear_algebra,
            array[i].programming,
            array[i].english,
            array[i].history
        );*/
        
        printf("|%15s|", array[i].surname);
        printf("     %s|", array[i].initials);
        printf("       %s|", array[i].gender);
        printf("%s|", array[i].group);
        printf("%10d|", array[i].calculus);
        printf("%16d|", array[i].linear_algebra);
        printf("%13d|", array[i].programming);
        printf("%9d|", array[i].english);
        printf("%9d|\n", array[i].history);
        printf("-----------------------------------------------------------------------------------------------------------\n");
    }
}

void pre_read()
{
    FILE *f = fopen("marks.bin", "rb");
    check_file_existence(f);
    fread(&students, sizeof(student), students_length, f);
    fclose(f);
}

void read_file()
{
    pre_read();
    print_file(students);
}


void count_scholars()
{
    pre_read();

    printf("Enter a group name (7 symbols):\n");
    char p[group_LENGTH];
    scanf("%7s", p);
    int count = 0;
    for (int i = 0; i < students_length; i++)
    {
        if ((!strcmp(students[i].group, p)) && (!strcmp(students[i].gender, "f")) && (students[i].calculus > 3) && (students[i].linear_algebra > 3) && (students[i].programming > 3) && (students[i].english > 3) && (students[i].history > 3))
        {
            count++;
        }
    }
    printf("The number of female students of the group %s, receiving scholarship: %d\n", p, count);
    
}
