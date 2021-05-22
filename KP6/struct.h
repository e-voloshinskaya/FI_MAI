#ifndef struct_h_
#define struct_h_

#define students_length 5
#define surname_LENGTH 15
#define initials_LENGTH 5
#define group_LENGTH 7

typedef struct {
	char surname[surname_LENGTH];
	char initials[initials_LENGTH];
	char gender[1];
	char group[group_LENGTH];
	int calculus;
	int linear_algebra;
    int programming;
    int english;
    int history;
} student;

void write_file();
void read_file();
void count_scholars();

student MAI_students[students_length] = {
	{"Balashov", "A. S.", 'm', "8O-107B", 5, 4, 4, 3, 5},
	{"Kalinina", "E. V.", 'f', "8O-107B", 4, 5, 5, 4, 5},
	{"Nikolaeva", "K. P.", 'f', "8O-107B", 4, 4, 3, 5, 4},
	{"Andreeva", "V. I.", 'f', "8O-107B", 5, 5, 5, 5, 3},
	{"Berezina", "M. V.", 'f', "8O-107B", 4, 4, 5, 4, 4}


};
#endif