#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"


void check_file_existence(FILE *file)
{
    if (file == NULL) {
        fprintf(stderr, "I/O Error: can't open file\n");
        exit(1);
    }
}

void write_file()
{
    FILE *f = fopen("marks.bin", "wb");
    check_file_existence(f);
    fwrite(MAI_students, sizeof(student), students_length, f);
    fclose(f);
}


void print_file(student array[])
{
    printf("|    surname    | initials | gender | group | calculus | linear algebra | programming | english | history |\n");
    printf("-----------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < students_length; i++)
    {
        printf("|%15s|%10s|%8s|%7s|%10d|%16d|%13d|%9d|%9d|\n",
            array[i].surname,
            array[i].initials,
            array[i].gender,
            array[i].group,
            array[i].calculus,
            array[i].linear_algebra,
            array[i].programming,
            array[i].english,
            array[i].history
        );
        printf("-----------------------------------------------------------------------------------------------------\n");
    }
}

void read_file()
{
    FILE *f = fopen("marks.bin", "rb");
    check_file_existence(f);
    student students[students_length];
    fread(students, sizeof(student), students_length, f);
    fclose(f);
    print_file(students);
}


void count_scholars()
{
    FILE *f = fopen("marks.bin", "rb");
    check_file_existence(f);
    student s;
    int count;
    char p[group_LENGTH];
    for (int i = 0; i < students_length; i++)
    {
        if ((!strcmp(s.group, p)) && (!strcmp(s.gender, "f")) && (s.calculus > 3) && (s.linear_algebra > 3) &&
        (s.programming > 3) && (s.english > 3) && (s.history > 3))
        {
            count++;
        }
    }
    printf("Количество студенток группы %s, получающих стипедию: %d.", p, count);
    
}