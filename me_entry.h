#ifndef MATH_ENTRY_H
#define MATH_ENTRY_H
#include <windows.h>
#include "me_paint.h"

typedef struct math_entry_data {
    int request_size;
    int i_request;
    int start_x;
    int start_y;
    struct math_structure** requests;
} math_entry_data_t;

int me_extract_next_word(char* buf, int buf_size, char* nword, int nword_size);
void math_entry_handle(HWND hwndCtrl, struct math_entry_data* med, math_structure_blueprint_set_t* msbs);



void math_entry_data_free(math_entry_data_t* med);
math_entry_data_t* math_entry_data_create(int start_x, int start_y);
void math_entry_data_append(
    math_entry_data_t* med, math_structure_blueprint_t* msb, int x, int y, 
    math_structure_t** item_p_arr
);

#endif