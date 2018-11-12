#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "lab2.h"

FILE* open_database() {
	// 1. fopen the file "food.db" for binary reading AND writing ("rb+").
	
	// 2. check if it returned NULL.
	// 3. if so, print a message saying it couldn't open the file, and use exit(1) to exit.
	// 4. otherwise, the file was opened successfully, so return it.

	return NULL; // remove this.
}

int count_food(FILE* f) {
	// using the very last slide from the lecture 03 slides:
	// 1. determine the byte length of the file with that code
	// 2. divide the byte length by sizeof(Food) to get the count of Food instances
	// 3. return that.

	return 0; // remove this.
}

void read_food(FILE* f, Food* pfood, int i) {
	// 1. fseek to the i'th Food in f
	// 2. fread a Food into pfood (NOT &pfood)
}

void print_food(FILE* f, int i) {
	// 1. declare a Food variable and use read_food to read into it
	// 2. print out the fields of food in a nicely-formatted way (see 4_food_struct.c)
}

void write_food(FILE* f, Food* pfood, int i) {
	// 1. fseek to the i'th Food in f
	// 		i may be the very end of the file - this is fine! The new data will be appended
	// 		to the end of the file. You don't have to handle this case separately.
	// 2. fwrite a Food from pfood (NOT &pfood)
}
