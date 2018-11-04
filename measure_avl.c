#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "helper.h"
#include "measure_avl.h"

#define N 1000

int main(int argc, char **argv){

	char filename[50];
	int lines;
	int* reserv_num;
	Hotel_t* hotels;

	lines = 0;

	if(argc == 1) {
		strcpy(filename, "data.csv");
	} 

	else {
		strcpy(filename, argv[1]);
    }

	load(&hotels, &lines, &reserv_num, filename);


	printf("\t* * * * Measurements * * * *\n\n");
	printf("AVL-tree search.\n");

	searchMenu(hotels, lines);

	clear(hotels, lines, reserv_num);
	
	return 0;
}
