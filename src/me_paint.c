// typedef struct simple_string {
//     char* simple_string;
//     int width;
// } simple_string_t;
/**
 * Math print
 * - needs a list of equations and a scroll bar input value to show which is happening
 * - 
 */


#include <windows.h>
#include "me_paint.h"
#include "me_entry.h"
#include "me_structure_blueprint.h"

#define CLICK_SIZE 5
#define CLICK_COLOUR RGB(0xFF, 0x0, 0x0)



void paint_editable_box(struct box* box, HDC hdc) {
    HPEN pen = CreatePen(PS_SOLID, 2, CLICK_COLOUR); 
    HPEN oldPen = SelectObject(hdc, pen);
    
    int x = box->x;
    int y = box->y;

    struct delta_xy* delta_box = delta_xy_create_4(
        box->width,  0,          
        0,           box->height, 
        -box->width, 0,          
        0,           -box->height
    ); 

    struct delta_xy* delta_click = delta_xy_create_4(
        CLICK_SIZE,  0,          
        0,           CLICK_SIZE, 
        -CLICK_SIZE, 0,          
        0,           -CLICK_SIZE
    ); 

    for (int i = 0; i < delta_box->length; i++) {
        MoveToEx(hdc, x, y, NULL);
        x += delta_box->dx[i];
        y += delta_box->dy[i];
        LineTo(hdc, x, y);
    }
    
    delta_box->dx[0] = box->width - CLICK_SIZE;
    delta_box->dx[2] = -(box->width - CLICK_SIZE);
    delta_box->dy[1] = box->height - CLICK_SIZE;
    delta_box->dy[3] = -(box->height - CLICK_SIZE);
    
    for (int i = 0; i < delta_box->length; i++) {
        for (int i = 0; i < delta_click->length; i++) {
            MoveToEx(hdc, x, y, NULL);
            x += delta_click->dx[i]; 
            y += delta_click->dy[i];
            LineTo(hdc, x, y);
        }    

        x += delta_box->dx[i];
        y += delta_box->dy[i];
    }
    
    delta_xy_free(delta_box);
    delta_xy_free(delta_click);
    
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}

/**
 * Recursive thing that paints structure.
 */
void paint_math_structure(HDC hdc, struct math_structure* structure, int paint_box) {
    HFONT font = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial" );
    HFONT hOldFont = (HFONT)SelectObject(hdc, font);

    SetTextColor(hdc, RGB(0x0, 0x0, 0x0));
    SetBkMode(hdc, TRANSPARENT); // Transparent background

    // Paint Character  
    TextOut(hdc, structure->box->x, structure->box->y, structure->value, structure->value_len);

    if (paint_box) paint_editable_box(structure->box, hdc);

    for (int i = 0; i < structure->no_item; i++) {
        if (structure->item_p_arr[i] != NULL) paint_math_structure(hdc, structure->item_p_arr[i], paint_box);
    }


    SelectObject(hdc, hOldFont);
    DeleteObject(font);
}


// struct math_structure* math_structure_create(
//     math_structure_blueprint_t* msb, int x, int y, math_structure_t** item_arr
// ) {
//     struct math_structure* ms = malloc(sizeof(struct math_structure));
//     // box
//     ms->box = malloc(sizeof(struct box));
//     ms->box->height = msb->start_height;
//     ms->box->width = msb->start_width;
//     ms->box->x = x;
//     ms->box->y = y;
//     // v
//     if (msb->character != NULL) {
//         ms->character = malloc(sizeof(char) * CHARACTER_BUF_LENGTH);
//         strcpy(ms->character, msb->character);
//     }       
//     // item_arr
//     if (item_arr != NULL) {
//         ms->no_item = msb->item_delta_set->length;
//         ms->item_p_arr = malloc(sizeof(struct math_structure*) * ms->no_item);
//         for (int i = 0; i < ms->no_item; i++) {
//             ms->item_p_arr[i] = item_arr[i];
//         }
//     } else {
//         ms->no_item = 0;
//         ms->item_p_arr = NULL;
//     }
//     ms->flag_paint_box = FALSE;
//     return ms;
// }
// void math_structure_free(
//     math_structure_t* ms
// ) {
//     for (int i = 0; i < ms->no_item; i++) {
//         math_structure_free(ms->item_p_arr[i]);
//     } 
//     free(ms);
// }
// static struct item* static_integral_item_set[3] = {
//     (struct item) {.dx = 5, .dy = 0},
//     (struct item) {.dx = 5, .dy = 20},
//     (struct item) {.dx = 10, .dy = 10},
//     (struct item) {.dx = 40, .dy = 0}
// };
// static struct structure static_integral = {.character = 0x0283, .no_item = 4, .code = "int", .set = integral_item_set}; 

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////MATH PAINT\\\\//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void math_data_paint(HDC hdc, struct math_entry_data* med, int paint_box) {
    for (int i = 0; i < (med->i_request); i++) {
        paint_math_structure(hdc, med->requests[i], paint_box);
    }
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////MATH BLUEPRINT//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
