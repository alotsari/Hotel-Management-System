#ifndef __PROJECT_H__
#define __PROJECT_H__ 

typedef struct Date Date_t;
typedef struct Reservation Reservation_t;
typedef struct Hotel Hotel_t;
typedef struct Avl_node Node_t;

struct Date {
	int d;
	int m;
	int y;
};
 
struct Reservation{
	char name[56];
	Date_t checkinDate;
	int stayDurationDays;
};

struct Hotel{
	int id;
	char name[256];
	int stars;
	int numberOfRooms;
	Reservation_t *reservations;
};

struct Avl_node{
	int key;
	int height;
	struct Avl_node* left;
	struct Avl_node* right;
};


#endif
