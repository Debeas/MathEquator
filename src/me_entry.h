#ifndef MATH_ENTRY_H
#define MATH_ENTRY_H
#include <windows.h>
#include "me_paint.h"
#include "me_structure.h"

typedef struct math_entry_data {
    int request_size;
    int i_request;
    int start_x;
    int start_y;
    struct math_structure** requests;
} me_data_t;

/**
 * start_x and start_y are added at the painting and everything in head is 
 * relative to zero.
 */
typedef struct me_data_tree {
    int start_x;
    int start_y;
    int new_head_flag;
    int head_count;
    struct math_structure** head;
} me_data_tree_t;

typedef struct me_entry_state {
    int no_item;
} me_entry_state_t;

// typedef struct math_entry_data_node {
//     struct math_structure* structure;
//     int child_len;
//     struct math_entry_data_node* child_arr;
// } math_entry_data_node_t; 

// // Unused
// typedef struct math_node {
//     struct math_node** child_arr;
    
//     // For a structure say \sum or a function 
//     int child_len;
//     struct math_structure* structure_ptr;
    
//     // For a number or variable
//     char* value;
//     int value_len;
// } math_node_t;

int me_extract_next_word(char* buf, int buf_size, char* nword, int nword_size);
void me_handle(HWND hwndCtrl, struct math_entry_data* med, math_structure_blueprint_set_t* msbs);
void me_handle_2(HWND hwndCtrl, struct me_data_tree** ptr_data, math_structure_blueprint_set_t* msbs);

void me_data_free(me_data_t* med);
me_data_t* me_data_create(int start_x, int start_y);
void me_data_append(
    me_data_t* med, math_structure_blueprint_t* msb, int x, int y, 
    math_structure_t** item_p_arr
);


// Data Tree
me_data_tree_t* me_data_tree_create();
me_data_tree_free(me_data_tree_t* medt);
void me_data_tree_next_item_set(
    me_data_tree_t* med,
    math_structure_blueprint_t* msb, // blueprint ptr
    math_structure_t** cur, 
    char* value,
    int value_len
);

// Already Exists in the math_structure and math_structure_blueprint
// math_node_t* math_node_create(math_structure_t* ms);
// void math_node_free(math_node_t* mn);

#endif