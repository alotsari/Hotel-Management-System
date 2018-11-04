#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "helper.h"
#include "functions.h"

#define N 1000

int main(int argc, char **argv){

	char filename[50];
	int lines, c, i, rand_i;
	int* reserv_num;
	double t1, t2, sum;
	struct timeval t;
	Hotel_t* hotels;

	lines = 0;
	sum = 0;

	if(argc == 1) {
		strcpy(filename, "data.csv");
	} 

	else {
		strcpy(filename, argv[1]);
    }

	load(&hotels, &lines, &reserv_num, filename);


	printf("\t* * * * Measurements * * * *\n\n");
	printf("Select type of search:\n");
	printf("1.Linear.\n");
	printf("2.Binary.\n");
	printf("3.Interpolation.\n");
	printf("-> ");

	scanf("%d", &c);

	switch(c){
		case 1: 
			for(i = 0; i < N; i++){
				rand_i = rand() % lines;
				
				gettimeofday(&t, NULL);
				t1 = t.tv_sec*1.0e6 + t.tv_usec;

				search(hotels, lines, rand_i);

				gettimeofday(&t, NULL);
				t2 = t.tv_sec*1.0e6 + t.tv_usec;

				sum = sum + (t2 -t1);
		}
				break;
		case 2: 
			for(i = 0; i < N; i++){
				rand_i = rand() % lines;
				sort(hotels, lines, reserv_num);
				
				gettimeofday(&t, NULL);
				t1 = t.tv_sec*1.0e6 + t.tv_usec;

				binary(hotels, lines, rand_i);
				
				gettimeofday(&t, NULL);
				t2 = t.tv_sec*1.0e6 + t.tv_usec;

				sum = sum + (t2 - t1);
			}
				break;
		case 3:
			for(i = 0; i < N; i++){
				rand_i = rand() % lines;
				sort(hotels, lines, reserv_num);			
	
				gettimeofday(&t, NULL);
				t1 = t.tv_sec*1.0e6 + t.tv_usec;

				interpolation(hotels, lines, rand_i);	

				gettimeofday(&t, NULL);
				t2 = t.tv_sec*1.0e6 + t.tv_usec;

				sum = sum + (t2 - t1);	
			}
				break;
	}
	printf("\nAverage time: %f usec.\n\n", sum/N);

	clear(hotels, lines, reserv_num);
	
	return 0;
}
