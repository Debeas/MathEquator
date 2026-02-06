#ifndef ME_PAINT_H
#define ME_PAINT_H

#include "me_structure_blueprint.h"

// Math Structure Blueprint

// typedef int TEST_FUNC_T;



// Math structure

struct item {
    int Reference_Mode;
    int dx;
    int dy;
};

typedef struct math_structure {
    char* code;
    char* character;
    int paint_box;
    int no_item;
    struct math_structure** item_p_arr; // Pointer to stuff
    struct box* box;
} math_structure_t;

struct box {
    int x;
    int y;
    int width;
    int height;
};

// Function Prototypes

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////MATH BLUEPRINT//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////




void math_structure_free(
    math_structure_t* ms
); 

struct math_structure* math_structure_create(
    math_structure_blueprint_t* msb, int x, int y, math_structure_t** item_arr
);

void math_data_paint(HDC hdc, struct math_entry_data* med_main);
void paint_math_structure(HDC hdc, struct math_structure* structure);
#endif