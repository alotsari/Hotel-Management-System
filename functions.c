#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "functions.h"

#define BUF_SIZE 1024


/******************* L O A D *******************/


void load(Hotel_t** hotels, int* line_num, int** reserv_num, char* filename){

	FILE* fp;
	char* data;
	char buffer[BUF_SIZE];
	int lines, i, j;
	int* res_num;
	Hotel_t* local_hotel;

	lines = 0;

	fp = fopen(filename, "r+");
	if (fp == NULL) {
		perror ("open");
		exit(1);
	}

	fgets(buffer,BUF_SIZE,fp);
	data = strtok(buffer,";");
	lines = atoi(data);

	local_hotel = malloc(lines * sizeof(Hotel_t));	
	res_num = malloc(lines * sizeof(int));		
	
	if(lines != 0){
		i = 0;

		while(fgets(buffer, BUF_SIZE, fp) != NULL) {		
			data = strtok(buffer, ";");
			local_hotel[i].id = atoi(data);									

			data = strtok(NULL, ";");
			strcpy(local_hotel[i].name,data);						
		
			data = strtok(NULL, ";");
			local_hotel[i].stars = atoi(data);                              
		
			data = strtok(NULL, ";");
			local_hotel[i].numberOfRooms = atoi(data);                              

			local_hotel[i].reservations = malloc(0 * sizeof(Reservation_t));
			res_num[i] = 0;
			j = 0;
	
			while ((data = strtok(NULL, ";")) != NULL){
	
				local_hotel[i].reservations = realloc(local_hotel[i].reservations, (j + 1) * sizeof(Reservation_t));
				res_num[i]++;

				strcpy(local_hotel[i].reservations[j].name,data);

				data = strtok(NULL, "/");
				local_hotel[i].reservations[j].checkinDate.d = atoi(data);
				data = strtok(NULL, "/");
				local_hotel[i].reservations[j].checkinDate.m = atoi(data);
				data = strtok(NULL, ";");
				local_hotel[i].reservations[j].checkinDate.y = atoi(data);

				data = strtok(NULL, ";");
				local_hotel[i].reservations[j].stayDurationDays = atoi(data);

				j++;
			}
		
			*reserv_num = res_num;
			i++;
		}
	}

	fclose(fp);

	*hotels = local_hotel;
	*line_num = lines;	

	printf("\nData were loaded successfully.\n\n");

	return;
}


/******************* S A V E *******************/


void save(Hotel_t* hotels, int lines, int* reserv_num, char* filename){

	FILE* fp;
	int i, j;

	fp = fopen(filename, "w+");	
	if (fp == NULL) {
		perror ("open");
		exit(1);
	}

	fprintf(fp, "%d;\n", lines);

	for(i = 0; i < lines; i++){
		fprintf(fp, "%d;%s;%d;%d", hotels[i].id, hotels[i].name, hotels[i].stars, hotels[i].numberOfRooms); 

		for(j = 0; j < reserv_num[i]; j++){
			fprintf(fp,";%s;%d/%d/%d;%d", hotels[i].reservations[j].name, hotels[i].reservations[j].checkinDate.d, hotels[i].reservations[j].checkinDate.m, hotels[i].reservations[j].checkinDate.y, hotels[i].reservations[j].stayDurationDays);
		}
		fprintf(fp,"\n");
	}

	fclose(fp);

	return;
}


/******************* A D D *******************/


void add(Hotel_t** hotels, int* line_num, int** numOfReserv){
	int id, i, j;
	char ans;
	Hotel_t* local_hotel;
	int* reserv_num;

	local_hotel = *hotels;
	reserv_num = *numOfReserv;

	while(1){

		printf("\nEnter hotel ID: ");
		scanf("%d", &id);
	
		i = 0;
		do{
			if(local_hotel[i].id == id){
				printf("\nThis ID already exits. Try again!\n");
				break;
			}
			i++;
		}while(i < (*line_num));

		if((*line_num) == i){
			
			local_hotel = realloc(local_hotel, (*line_num + 1) * sizeof(Hotel_t));
			reserv_num = realloc(reserv_num, (*line_num + 1) * sizeof(int));

			local_hotel[*line_num].id = id;
			reserv_num[*line_num] = 0;		

			printf("Enter hotel name: ");			

			getchar();
			fgets(local_hotel[*line_num].name, 256, stdin);
			strtok(local_hotel[*line_num].name,"\n");

			printf("Enter number of stars: ");
			scanf("%d", &local_hotel[*line_num].stars);
			printf("Enter number of rooms: ");
			scanf("%d", &local_hotel[*line_num].numberOfRooms);
			
			j = 0;
			local_hotel[*line_num].reservations = malloc(j * sizeof(Reservation_t));			
				
			while(1){

				printf("\nDo you want to add a reservarion? (y/n) ");
				scanf("%s", &ans);
				if(ans != 'y'){
					break;
				}
			
				local_hotel[*line_num].reservations = realloc(local_hotel[*line_num].reservations, (j + 1) * sizeof(Reservation_t));
				reserv_num[*line_num]++;

				printf("\nEnter name: ");

				getchar();		
				fgets(local_hotel[*line_num].reservations[j].name, 56, stdin);
				strtok(local_hotel[*line_num].reservations[j].name,"\n");

				printf("Enter check in date\nDay: ");
				scanf("%d",&local_hotel[*line_num].reservations[j].checkinDate.d);
				printf("Month: ");		
				scanf("%d",&local_hotel[*line_num].reservations[j].checkinDate.m);
				printf("Year: ");		
				scanf("%d",&local_hotel[*line_num].reservations[j].checkinDate.y);
				printf("Enter stay duration days: ");
				scanf("%d",&local_hotel[*line_num].reservations[j].stayDurationDays);

				j++;
			}	
			break;		
		}
	}
		
	*hotels = local_hotel;
	*numOfReserv = reserv_num;
	++*line_num;

	printf("\nHotel was added successfully.\n\n");

	return;
}


/******************* S E A R C H *******************/


void search(Hotel_t* hotels, int lines, int id){
	
	int i, flag;

	flag = 0;

	for(i = 0; i < lines; i++){
		if(hotels[i].id == id){
			printf("\nHotel name: %s\n", hotels[i].name);
			printf("Stars: %d\n", hotels[i].stars);
			printf("Number of rooms: %d\n\n", hotels[i].numberOfRooms);
	
			flag = 1;
			break;
		}
	}

	if(flag == 0){
		printf("\nThis ID doesn't exist.\n\n");
	}

	return;
}


/******************* B I N A R Y *******************/


void binary(Hotel_t* hotels, int lines, int id){

	int first, middle, last;

	first = 0;
	last = lines - 1;
	middle = (first + last)/2;

	while(first <= last){

		if(id > hotels[middle].id){
			first = middle + 1;
		}
		else if(id < hotels[middle].id){
			last = middle - 1;
		}
		else{
			printf("\nHotel name: %s\n", hotels[middle].name);
			printf("Stars: %d\n", hotels[middle].stars);
			printf("Number of rooms: %d\n\n", hotels[middle].numberOfRooms);

			break;	
		}
		
		middle = (first + last)/2;
	}

	if(first > last){
		printf("\nThis ID doesn't exist.\n\n");
	}

	return;
}


/******************* I N T E R P O L A T I O N *******************/


void interpolation(Hotel_t* hotels, int lines, int id){

	int first, middle, last, flag;

	flag = 0;
	first = 0;
	last = lines - 1;

	while((hotels[last].id != hotels[first].id)   && (id >= hotels[first].id )  && (id <= hotels[last].id)  ){

		middle = first + ((id - hotels[first].id)  * (last - first) / (hotels[last].id - hotels[first].id) );

		if(id > hotels[middle].id){
			first = middle + 1;
		}
		else if(id < hotels[middle].id) {
			last = middle - 1;
		}
		else{
			printf("\nHotel name: %s\n", hotels[middle].name);
			printf("Stars: %d\n", hotels[middle].stars);
			printf("Number of rooms: %d\n\n", hotels[middle].numberOfRooms);
			
			flag = 1;
			break;
		}
	}

	if((id == hotels[first].id) && (flag == 0)) {
		printf("\nHotel name: %s\n", hotels[first].name);
		printf("Stars: %d\n", hotels[first].stars);
		printf("Number of rooms: %d\n\n", hotels[first].numberOfRooms);

		flag = 1;
	}
	
	if(flag == 0){
		printf("\nThis ID doesn't exist.\n\n");
	}
		
	return;
}


/******************* D I S P L A Y *******************/
 

void display(Hotel_t* hotels, int lines, int* reserv_num){

	int i, j, flag;
	char name[56];

	flag = 0;

	printf("\nEnter surname: ");
	scanf("%s", name);
	printf("\n");

	for(i = 0; i < lines; i++){
		for(j = 0; j < reserv_num[i]; j++){
			if(strcmp(name, hotels[i].reservations[j].name) == 0){
				flag = 1;

				printf("Hotel: %s\n", hotels[i].name);
				printf("Date: %d/%d/%d\n", hotels[i].reservations[j].checkinDate.d, hotels[i].reservations[j].checkinDate.m, hotels[i].reservations[j].checkinDate.y);	
				printf("Duration: %d\n\n", hotels[i].reservations[j].stayDurationDays);
			}
		}
	}

	if(flag == 0){
		printf("%s did't make any reservation.\n\n", name);
	}

	return;

}


/******************* S E A R C H  M E N U *******************/


void searchMenu(Hotel_t* hotels, int lines, int* reserv_num, int id){

	int typeOfSearch;

	printf("\nSelect type of search:\n");
	printf("1.Linear search.\n");
	printf("2.Binary search.\n");
	printf("3.Interpolation search.\n");
	printf("-> ");
	scanf("%d", &typeOfSearch);				

	if(typeOfSearch == 1){
		search(hotels, lines, id);
	}
	else if(typeOfSearch == 2){
		sort(hotels, lines, reserv_num);
		binary(hotels, lines, id);
	}
	else if(typeOfSearch == 3){
		sort(hotels, lines, reserv_num);
		interpolation(hotels, lines, id);
	}
	else{
		printf("\nNo such choice.\n\n");
	}
}


/******************* S O R T I N G *******************/


void sort(Hotel_t* hotels, int lines, int* reserv_num){

	int i, j, temp1;
	Hotel_t temp2; 

	for(i = 1; i < lines; i++){
		for(j = 0; j < lines - i; j++){
			if(hotels[j].id > hotels[j + 1].id){
				temp1 = reserv_num[j];
				reserv_num[j] = reserv_num[j + 1];
				reserv_num[j + 1] = temp1;

				temp2 = hotels[j];
				hotels[j] = hotels[j + 1];
				hotels[j + 1] = temp2;
			}
		}
	}

}


/******************* C L E A R *******************/


void clear(Hotel_t* hotels, int lines, int* reserv_num){

	int i;

	for(i = 0; i < lines; i++) {	
		free(hotels[i].reservations);
	}

	free(hotels);	
	free(reserv_num);
}
