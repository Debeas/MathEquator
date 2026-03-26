#include "me_structure.h"
#include <stdlib.h>
#include <windef.h>

/**
 * 
 */
struct math_structure* math_structure_create(
    math_structure_blueprint_t* msb, int x, int y, math_structure_t** item_arr
) {
    struct math_structure* ms = malloc(sizeof(math_structure_t));

    // box
    ms->box = malloc(sizeof(box_t));
    ms->box->height = msb->start_height;
    ms->box->width = msb->start_width;
    ms->box->x = x;
    ms->box->y = y;

    // Setting the value if the value can be.
    if (msb->character != NULL) {
        ms->value = malloc(sizeof(char) * CHARACTER_BUF_LENGTH);
        strcpy(ms->value, msb->character);
    }
        
    // item_arr premake 
    if (item_arr != NULL) {
        ms->no_item = msb->item_delta_set->length;
        ms->item_p_arr = malloc(sizeof(struct math_structure*) * ms->no_item);
        for (int i = 0; i < ms->no_item; i++) {
            ms->item_p_arr[i] = item_arr[i];
        }
    } else {
        ms->no_item = 0;
        ms->item_p_arr = NULL;
    }
    

    ms->flag_paint_box = FALSE;
    return ms;
}

/**
 * Creates an empty math structure setting the childs to NULL
 */
struct math_structure* math_structure_create_childless(
    math_structure_blueprint_t* msb, int x, int y, char* value, int value_len
) {
    struct math_structure* ms = malloc(sizeof(math_structure_t));

    // box
    ms->box = malloc(sizeof(box_t));
    ms->box->height = msb->start_height;
    ms->box->width = msb->start_width;
    ms->box->x = x;
    ms->box->y = y;

    // Setting the value if the value can be.
    if (value != NULL && value_len != 0) {
        ms->value = malloc(sizeof(char) * CHARACTER_BUF_LENGTH);
        ms->value_len = value_len; 
        strcpy(ms->value, value);
    }
        
    // item_arr premake 
    
    // Setting the number of child
    ms->next_item_i = 0;
    ms->no_item = msb->item_delta_set->length;
    ms->item_p_arr = malloc(sizeof(struct math_structure*) * ms->no_item);
    for (int i = 0; i < ms->no_item; i++) {
        ms->item_p_arr[i] = NULL;
    }    

    ms->flag_paint_box = FALSE;
    return ms;
}

void math_structure_free(
    math_structure_t* ms
) {
    for (int i = 0; i < ms->no_item; i++) {
        math_structure_free(ms->item_p_arr[i]);
    }
    
    free(ms);
}

