#include "me_structure_blueprint.h"
#include <windows.h>
#include <string.h>

/**
 * Code Symbols for the TeX, need to have the the things with the backslash
 * 
 * Integral
 * Cases
 * Exponent
 * 
 * Functions: Log Sin
 * 
 * Needs to be read from a file, so need to go back and work on program diagram
 * -ahhh.
 * 
 * Stupid system everything has a parent open bracket has its closing bracket as
 * a child.
 */
math_structure_blueprint_set_t* math_structure_blueprint_set_defining() {
    math_structure_blueprint_set_t* msbs = math_structure_blueprint_set_create();

    // sin(x)
    struct delta_xy* sin_delta = delta_xy_create_first(15, 0, MP_DEFAULT_START_HEIGHT);
    math_structure_blueprint_set_append(
        msbs,
        "\\sin", // code
        "sin", // character
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        sin_delta, 
        NULL // check_func
    );

    // cos(x)
    struct delta_xy* cos_delta = delta_xy_create_first(15, 0, MP_DEFAULT_START_HEIGHT);
    math_structure_blueprint_set_append(
        msbs,
        "\\cos", // code
        "cos", // character
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        cos_delta,
        NULL // check_func
    );
    
    // tan(x)
    struct delta_xy* tan_delta = delta_xy_create_first(15, 0, MP_DEFAULT_START_HEIGHT);
    math_structure_blueprint_set_append(
        msbs,
        "\\tan", // code
        "tan", // character
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        tan_delta,
        NULL // check_func
    );

    // ln(x)
    struct delta_xy* ln_delta = delta_xy_create_first(10, 0, MP_DEFAULT_START_HEIGHT);
    math_structure_blueprint_set_append(
        msbs,
        "\\ln", // code
        "ln", // character
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        ln_delta,
        NULL // check_func
    );

    // Exponent
    struct delta_xy* exponent_delta = delta_xy_create_first(0, 0, MP_DEFAULT_START_HEIGHT);
    delta_xy_append(exponent_delta, 5, -5, MP_DEFAULT_START_HEIGHT);
    math_structure_blueprint_set_append(
        msbs,
        "\\exp", // code
        "", // character
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        ln_delta,
        NULL // check_func
    );

    // Integral (upper bound, lower bound, inside, integrating variable)
    struct delta_xy* integral_delta = delta_xy_create_first(5, 0, MP_DEFAULT_START_HEIGHT);
    delta_xy_append(integral_delta, 5, 20, MP_DEFAULT_START_HEIGHT);
    delta_xy_append(integral_delta, 10, -10, MP_DEFAULT_START_HEIGHT);
    delta_xy_append(integral_delta, 5, 0, MP_DEFAULT_START_HEIGHT);
    math_structure_blueprint_set_append(
        msbs,
        "\\int", // code
        "\U0283", // character
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        integral_delta,
        NULL // check_func
    );

    // Derivative (deriving variable, expression)

    // Fraction (Numerator, Denominator)

    // Open Bracket
    struct delta_xy* open_bracket_delta = delta_xy_create_first(5, 0, MP_DEFAULT_START_HEIGHT);
    delta_xy_append(open_bracket_delta, 10, 0, MP_DEFAULT_START_HEIGHT);
    math_structure_blueprint_set_append(
        msbs,
        "(", // code
        "(", // character
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        open_bracket_delta,
        NULL // check_func
    );
    
    // Close Bracket
    math_structure_blueprint_set_append(
        msbs,
        ")", // code
        ")", // character
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        NULL,
        NULL // check_func
    );

    // Variable 
    math_structure_blueprint_set_append(
        msbs,
        "",
        "",
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        NULL,
        cf_alphabetic_singular
    );

    for (int i = 0; i < msbs->msb_i; i++) {
        printf("%d: code=%s\n", i, msbs->msb_arr[i].code);
    }
    

    return msbs;
} 




struct delta_xy* delta_xy_create_4(
    int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4
) {
    struct delta_xy* delta_grand = malloc(sizeof(struct delta_xy));
    delta_grand->length = 4;
    delta_grand->dx = calloc(4, sizeof(struct delta_xy));
    delta_grand->dy = calloc(4, sizeof(struct delta_xy));

    delta_grand->dx[0] = x1; delta_grand->dy[0] = y1;
    delta_grand->dx[1] = x2; delta_grand->dy[1] = y2;
    delta_grand->dx[2] = x3; delta_grand->dy[2] = y3;
    delta_grand->dx[3] = x4; delta_grand->dy[3] = y4;

    return delta_grand;
}

void delta_xy_free(struct delta_xy* s) {
    free(s->dx);
    free(s->dy);
    free(s);
}


#pragma region Math BluePrint


struct delta_xy* delta_xy_create_first(int dx, int dy, int height) {
    struct delta_xy* delta = malloc(sizeof(struct delta_xy));
    delta->length = 1;

    delta->dx = malloc(sizeof(int)); 
    delta->dx[0] = dx;
    
    delta->dy = malloc(sizeof(int)); 
    delta->dy[0] = dy;
    
    delta->height = malloc(sizeof(int)); 
    delta->height[0] = height;
    
    return delta;
}

struct delta_xy* delta_xy_append(struct delta_xy* delta, int dx, int dy, int height) {
    delta->length++;
    int* new_dx = malloc(sizeof(int) * delta->length);
    int* new_dy = malloc(sizeof(int) * delta->length);
    int* new_height = malloc(sizeof(int) * delta->length);

    for (int i = 0; i < delta->length - 1; i++) {
        new_dx[i]       = delta->dx[i];
        new_dy[i]       = delta->dy[i];
        new_height[i]   = delta->height[i];
    }

    free(delta->dx);
    free(delta->dy);
    free(delta->height);

    delta->dx       = new_dx;    
    delta->dy       = new_dy;    
    delta->height   = new_height;    

    delta->dx[delta->length - 1] = dx;
    delta->dy[delta->length - 1] = dy;
    delta->height[delta->length - 1] = height;
    
    return delta;
}

math_structure_blueprint_t* math_structure_blueprint_create(
    char* code, char* character, int paint_box, /* int no_item, */ int start_width,
    int start_height, struct delta_xy* items_relevant
) {
    math_structure_blueprint_t* msb = malloc(sizeof(math_structure_blueprint_t));
    msb->code = code;
    msb->character = character;
    // msb->paint_box = paint_box;
    // msb->no_item = no_item;
    msb->start_width = start_width;
    msb->start_height = start_height;
    msb->item_delta_set = items_relevant;
    return msb;
}

math_structure_blueprint_set_t* math_structure_blueprint_set_create() {
    math_structure_blueprint_set_t* msbs = malloc(sizeof(math_structure_blueprint_set_t));
    msbs->msb_arr = NULL;
    msbs->msb_i = 0;
    msbs->msb_size = 0;
    return msbs;
}


void math_structure_blueprint_copy(
    math_structure_blueprint_t* msb_store,
    math_structure_blueprint_t* msb_source
) {
    msb_store->code             = msb_source->code;
    msb_store->character        = msb_source->character;
    // msb_store->paint_box        = msb_source->paint_box;
    msb_store->start_width      = msb_source->start_width;
    msb_store->start_height     = msb_source->start_height;
    // msb_store->no_item          = msb_source->no_item;
    msb_store->item_delta_set   = msb_source->item_delta_set;
}

void math_structure_blueprint_set_append(
    math_structure_blueprint_set_t* msbs, 
    char* code, 
    char* character, 
    // int paint_box, 
    // int no_item, 
    int start_width, 
    int start_height, 
    struct delta_xy* item_delta_set,
    CHECK_FUNC_T check_func
) {
    if (msbs->msb_arr == NULL || msbs->msb_size == 0) {
        msbs->msb_size++;
        msbs->msb_arr = malloc(sizeof(math_structure_blueprint_t));
    } else if (msbs->msb_i >= msbs->msb_size) {
        msbs->msb_size *= 2;
        math_structure_blueprint_t* new_arr = malloc(
            msbs->msb_size * sizeof(math_structure_blueprint_t)
        );

        for (int i = 0; i < msbs->msb_i; i++) {
            math_structure_blueprint_copy(&(new_arr[i]), &(msbs->msb_arr[i]));
        }

        free(msbs->msb_arr);
        msbs->msb_arr = new_arr;
    }

    msbs->msb_arr[msbs->msb_i].code = code;
    msbs->msb_arr[msbs->msb_i].character = character;
    // msbs->msb_arr[msbs->msb_i].paint_box = paint_box;
    msbs->msb_arr[msbs->msb_i].start_height = start_height;
    msbs->msb_arr[msbs->msb_i].start_width = start_width;
    // msbs->msb_arr[msbs->msb_i].no_item = no_item;
    msbs->msb_arr[msbs->msb_i].item_delta_set = item_delta_set;
    msbs->msb_arr[msbs->msb_i].check_func = check_func;
    msbs->msb_i++;
}

void math_structure_blueprint_set_test_print(
    math_structure_blueprint_set_t* msbs
) {
    printf("Mathematical Structure Blueprint set\n"); 
    printf("\tno_elements: %d\n", msbs->msb_i);
    printf("\n");
    for (int i = 0; i < msbs->msb_i; i++) {
        printf("%d:\n", i);
        printf("\tcode=%s\n", msbs->msb_arr[i].code);
        printf("\tcharacter=%s\n", msbs->msb_arr[i].character);
        // printf("\tpaint_box=%d\n", msbs->msb_arr[i].paint_box);
        printf("\tstart_height=%d\n", msbs->msb_arr[i].start_height);
        printf("\tstart_width=%d\n", msbs->msb_arr[i].start_width);
        printf("\titem length=%d\n", msbs->msb_arr[i].item_delta_set->length);
        for (int i2 = 0; i2 < msbs->msb_arr[i].item_delta_set->length; i2++) {
            printf(
                "\t\t%d: dx,dy=(%d, %d) height=%d\n", 
                i,  
                msbs->msb_arr[i].item_delta_set->dx[i2],
                msbs->msb_arr[i].item_delta_set->dy[i2],
                msbs->msb_arr[i].item_delta_set->height[i2]
            );
        }
    }
}

void math_structure_blueprint_set_free(math_structure_blueprint_set_t* msbs) {
    for (int i = 0; i < msbs->msb_i; i++) {
        for (int i2 = 0; i2 < msbs->msb_arr[i].item_delta_set->length; i2++) {
            free(msbs->msb_arr[i].item_delta_set->dx);
            free(msbs->msb_arr[i].item_delta_set->dy);
            free(msbs->msb_arr[i].item_delta_set->height);
        }
        
        free(msbs->msb_arr[i].item_delta_set);
    }
    
    free(msbs->msb_arr);
    free(msbs);
}


int cf_alphabetic_singular(char* c) {
    return  (
        ('a' <= c[0] && c[0] <= 'z') || ('A' <= c[0] && c[0] <= 'Z')
    ) && c[1] == '\0';
}

#pragma endregion Math BluePrint