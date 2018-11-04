#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "helper.h"
#include "functions.h"

int main(int argc, char **argv){

	char filename[50];
	int c, lines, fflag, id;
	int* reserv_num;
	Hotel_t* hotels;

	lines = 0;
	fflag = 0;

	if(argc == 1) {
		strcpy(filename, "data.csv");
	} 

	else {
		strcpy(filename, argv[1]);
    }

	do{

		printf("\t* * * * MENU * * * *\n");
		printf("1. Load Hotels and Reservations from file.\n");
		printf("2. Save Hotels and Reservations to file.\n");
		printf("3. Add a Hotel.\n");
		printf("4. Search and Display a Hotel by id.\n");
		printf("5. Display Reservations by surname search.\n");
		printf("6. Exit.\n");
		printf("-> ");

		scanf("%d",&c);
		if ((c < 1) || (c > 6)) {
			printf("Wrong choice, try again! \n\n");
		}

		else {

			switch(c){

				case 1:
					if(fflag == 0){
						load(&hotels, &lines, &reserv_num, filename);
					}
					else{
						printf("\nLoading completed.\n\n");
					}

					fflag = 1;
					break;
				case 2:
					if(fflag == 0){
						printf("\nNo file loaded.\n\n");						
					}
					else{
						save(hotels, lines, reserv_num, filename);
						printf("\nSaved.\n\n");
					}

					break;
				case 3:
					if(fflag == 0){
						printf("\nNo file loaded.\n\n");						
					}
					else{
						add(&hotels, &lines, &reserv_num);
					}

					break;
				case 4:
					if(fflag == 0){
						printf("\nNo file loaded.\n\n");						
					}
					else{
						printf("\nEnter ID: ");
						scanf("%d", &id);
						searchMenu(hotels, lines, reserv_num, id);
					}

					break;
				case 5:
					if(fflag == 0){
						printf("\nNo file loaded.\n\n");						
					}
					else{
						display(hotels, lines, reserv_num);
					}

					break;
				case 6:
					if(fflag == 0){
						printf("\nExit.\n\n");					
					}
					else{
						save(hotels, lines, reserv_num, filename);
						printf("\nExit. File Saved.\n\n");
					}

					break;
				default:
					printf("Wrong choice, try again! \n\n");
			}
		}

	}while(c != 6);
	
	if(fflag == 1){
		clear(hotels, lines, reserv_num);
	}

	return 0;
}
