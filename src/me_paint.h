#ifndef ME_PAINT_H
#define ME_PAINT_H

#include "me_structure.h"
#include <windows.h>

// Math Structure Blueprint

// typedef int TEST_FUNC_T;



// Math structure

struct item {
    int Reference_Mode;
    int dx;
    int dy;
};



// Function Prototypes

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////MATH BLUEPRINT//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////





void math_data_paint(HDC hdc, struct math_entry_data* med_main, int paint_box);
void paint_math_structure(HDC hdc, struct math_structure* structure, int paint_box);
#endif