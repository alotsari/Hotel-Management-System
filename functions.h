#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

void load(Hotel_t** hotels, int* lines, int** reserv_num, char* filename);
void save(Hotel_t* hotels, int lines, int* reserv_num, char* filename);
void add(Hotel_t** hotels, int* lines, int** reserv_num);
void search(Hotel_t* hotels, int lines, int id);
void searchMenu(Hotel_t* hotels, int lines, int* reserv_num, int id);
void binary(Hotel_t* hotels, int lines, int id);
void interpolation(Hotel_t* hotels, int lines, int id);
void display(Hotel_t* hotels, int lines, int* reserv_num);
void sort(Hotel_t* hotels, int lines, int* reserv_num);
void clear(Hotel_t* hotels, int lines, int* reserv_num);

#endif
