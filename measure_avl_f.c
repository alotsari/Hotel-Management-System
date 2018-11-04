#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "helper.h"
#include "measure_avl.h"

#define N 1000
#define BUF_SIZE 1024

Node_t* tree;

/******************* L O A D *******************/


void load(Hotel_t** hotels, int* line_num, int** reserv_num, char* filename){

	FILE* fp;
	char* data;
	char buffer[BUF_SIZE];
	int lines, i, j;
	int* res_num;
	Hotel_t* local_hotel;

	tree = NULL;
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
	
			tree = insert(local_hotel, tree, i);
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


/******************* A V L  S E A R C H *******************/


void avl_search(Hotel_t* hotels, Node_t* n, int id){
	
	if(n == NULL){
			;					/*Node doesn't exist.*/
	}
	else{
		if(id == hotels[n->key].id){
			;					/*Search completed successfully.*/
		}
		else if(id < hotels[n->key].id){
			avl_search(hotels, n->left, id);
		}
		else if(id > hotels[n->key].id){
			avl_search(hotels, n->right, id);
		}
	}
	return;
}


/******************* S E A R C H  M E N U *******************/


void searchMenu(Hotel_t* hotels, int lines){
	
	int i, rand_i;
	double t1, t2, sum;
	struct timeval t; 
	
	for(i = 0; i < N; i++){
		rand_i = rand() % lines;
				
		gettimeofday(&t, NULL);
		t1 = t.tv_sec*1.0e6 + t.tv_usec;

		avl_search(hotels, tree, rand_i);

		gettimeofday(&t, NULL);
		t2 = t.tv_sec*1.0e6 + t.tv_usec;

		sum = sum + (t2 -t1);
	}
	printf("\nAverage time: %f usec.\n\n", sum/N);
}


/******************* M A X *******************/


int max(int a, int b){
	return ((a < b) ? (b) : (a));
}


/******************* H E I G H T *******************/


int height(Node_t* n){
	if(n == NULL){
		return 0;
	}
	else{
		return n->height;
	}
}


/******************* B A L A N C E *******************/


int balance(Node_t* n){
	if(n == NULL){
		return 0;
	}
	else{
		return height(n->left) - height(n->right);
	}
}


/******************* RR  R O T A T I O N *******************/


Node_t* rr_rotation(Node_t* parent){
	Node_t* n;

	n = parent->right;
	parent->right = n->left;
	n->left = parent;

	parent->height = max(height(parent->left), height(parent->right)) + 1;

	n->height = max(height(n->right), parent->height) + 1;

	return n;
}


/******************* LL  R O T A T I O N *******************/


Node_t* ll_rotation(Node_t* parent){
	Node_t* n;

	n = parent->left;
	parent->left = n->right;
	n->right = parent;

	parent->height = max(height(parent->left), height(parent->right)) + 1;
	n->height = max(height(n->left), parent->height) + 1;

	return n;
}


/******************* RL  R O T A T I O N *******************/


Node_t* rl_rotation(Node_t* parent){
	Node_t* n;

	n = parent->right;
	parent->right = ll_rotation(n);

	return rr_rotation(parent);	
}


/******************* LR  R O T A T I O N *******************/


Node_t* lr_rotation(Node_t* parent){
	Node_t* n;

	n = parent->left;
	parent->left = rr_rotation(n);

	return ll_rotation(parent);	
}


/******************* B A L A N C I N G *******************/


Node_t* balancing(Node_t* n){
	int b_factor = balance(n);

	if(b_factor > 1){
		if(balance(n->left) > 0){
			n = ll_rotation(n);	
		}
		else{
			n = lr_rotation(n);
		}
	}
	else if(b_factor < -1){
		if(balance(n->right) > 0){
			n = rl_rotation(n);
		}
		else{
			n = rr_rotation(n);
		}
	}

	return n;
}


/******************* A V L  I N S E R T *******************/
 

Node_t* insert(Hotel_t* hotels, Node_t* root, int i){

	if(root == NULL){
		root = (Node_t*) malloc(sizeof(Node_t));
		root->key = i;
		root->left = NULL;
		root->right =NULL;
	}
	else if(hotels[i].id < hotels[root->key].id){
		root->left = insert(hotels, root->left, i);
		root = balancing(root);
	}
	else if(hotels[i].id > hotels[root->key].id){
		root->right = insert(hotels, root->right, i);
		root = balancing(root);
	}

	root->height = max(height(root->left), height(root->right)) + 1;
	
	return root;	
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


/******************* C L E A R  T R E E *******************/


void clear_tree(Node_t* n){

	if(n != NULL){
		clear_tree(n->left);
		clear_tree(n->right);
		free(n);
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

	clear_tree(tree);
}
