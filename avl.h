#ifndef __AVL_H__
#define __AVL_H__

void load(Hotel_t** hotels, int* lines, int** reserv_num, char* filename);
void save(Hotel_t* hotels, int lines, int* reserv_num, char* filename);
void add(Hotel_t** hotels, int* lines, int** reserv_num);
void avl_search(Hotel_t* hotels, Node_t* tree, int id);
void searchMenu(Hotel_t* hotels, int lines, int* reserv_num, int id);
void binary(Hotel_t* hotels, int lines, int id);
void interpolation(Hotel_t* hotels, int lines, int id);
void display(Hotel_t* hotels, int lines, int* reserv_num);
void sort(Hotel_t* hotels, int lines, int* reserv_num);
void clear(Hotel_t* hotels, int lines, int* reserv_num);
void clear_tree(Node_t* tree);

int max(int a, int b);
int height(Node_t* n);
int balance(Node_t* n);
Node_t* rr_rotation(Node_t* parent);
Node_t* ll_rotation(Node_t* parent);
Node_t* rl_rotation(Node_t* parent);
Node_t* lr_rotation(Node_t* parent);
Node_t* balancing(Node_t* n);
Node_t* insert(Hotel_t* hotels, Node_t* root, int i);

#endif
