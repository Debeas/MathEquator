#ifndef ME_STRUCTURE_H
#define ME_STRUCTURE_H

#include "me_structure_blueprint.h"
#include <stdlib.h> 
#include <windows.h> 

#define CHARACTER_BUF_LENGTH 50

/**
 * Really is the structure for painting,
 */
typedef struct math_structure {
    // code or character doesn't matter
    char* value;
    int value_len;
    struct math_structure_blueprint_t* ptr_bluep;
    
    // If the box is painted
    int flag_paint_box;
    
    // Box for painting is the show area,
    struct box* box;

    // Tree Structure
    struct math_structure* parent;  
    int no_item;
    int next_item_i;
    struct math_structure** item_p_arr; // Pointer to stuff
} math_structure_t;

typedef struct box {
    int x;
    int y;
    int width;
    int height;
} box_t;

void math_structure_free(
    math_structure_t* ms
); 

struct math_structure* math_structure_create(
    math_structure_blueprint_t* msb, int x, int y, math_structure_t** item_arr
);
struct math_structure* math_structure_create_childless(
    math_structure_blueprint_t* msb, int x, int y, char* value, int value_len
);

#endif