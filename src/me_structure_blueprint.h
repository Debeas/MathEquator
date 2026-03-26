#ifndef ME_STRUCTURE_BLUEPRINT_H
#define ME_STRUCTURE_BLUEPRINT_H

#define MP_DEFAULT_START_HEIGHT 20
#define MP_DEFAULT_START_WIDTH 50

#include <windows.h>


typedef int(*CHECK_FUNC_T)(char*);

typedef struct math_structure_blueprint_set {
    int msb_i; // next append loc
    int msb_size;
    struct math_structure_blueprint* msb_arr;

} math_structure_blueprint_set_t;

typedef struct math_structure_blueprint {
    char* name;
    char* code;
    char* character;
    int show_character;
    enum special_structure special;
    
    // int paint_box;
    int start_width;
    int start_height;

    // int item_count;
    struct delta_xy* item_delta_set;
    CHECK_FUNC_T check_func;
} math_structure_blueprint_t;

typedef struct delta_xy {
    int length;
    int* dx;
    int* dy;
    int* height;
} delta_xy_t;

enum special_structure {
    SINGLE_CHARACTER, NUMERIC, ALPHABETIC, ALPHANUMERIC
};


// blueprint set
math_structure_blueprint_set_t* math_structure_blueprint_set_defining();
void math_structure_blueprint_set_test_print(
    math_structure_blueprint_set_t* msbs
);
math_structure_blueprint_set_t* math_structure_blueprint_set_create();
void math_structure_blueprint_set_free(math_structure_blueprint_set_t* msbs);
void math_structure_blueprint_set_append(
    math_structure_blueprint_set_t* msbs, 
    char* name, 
    char* code, 
    char* character, 
    // int paint_box, 
    // int no_item, 
    int start_width, 
    int start_height, 
    struct delta_xy* item_delta_set,
    CHECK_FUNC_T check_func
);

// delta x y
struct delta_xy* delta_xy_append(struct delta_xy* delta, int dx, int dy, int height);
struct delta_xy* delta_xy_create_first(int dx, int dy, int height);
struct delta_xy* delta_xy_create_4(
    int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4
);

// blueprint 
void math_structure_blueprint_copy(
    math_structure_blueprint_t* msb_store,
    math_structure_blueprint_t* msb_source
);
void math_structure_blueprint_free(math_structure_blueprint_t* msb);

// Check Function 
int cf_alphabetic_singular(char* c);


#endif