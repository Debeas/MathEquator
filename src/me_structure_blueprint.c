#include "me_structure_blueprint.h"
#include <windows.h>
#include <string.h>
#define TEST_MMSBSD 0


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
#define MSBSD_NULL_TO_STRING(a) (a == NULL ? "NULL" : a)
math_structure_blueprint_set_t* math_structure_blueprint_set_defining() {
    math_structure_blueprint_set_t* msbs = math_structure_blueprint_set_create();

    // Blank/Hold/Space
    math_structure_blueprint_set_append(
        msbs, 
        "Blank",
        "\\blank",
        "[]",
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        NULL, 
        NULL, // check func
        SINGLE_CHARACTER
    );

    // sin(x)
    struct delta_xy* sin_delta = delta_xy_create_first(15, 0, MP_DEFAULT_START_HEIGHT);
    math_structure_blueprint_set_append(
        msbs,
        "Sin Function",
        "\\sin", // code
        "sin", // character
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        sin_delta, 
        NULL, // check func
        SINGLE_CHARACTER
    );

    // cos(x)
    struct delta_xy* cos_delta = delta_xy_create_first(15, 0, MP_DEFAULT_START_HEIGHT);
    math_structure_blueprint_set_append(
        msbs,
        "Cos Function", // name
        "\\cos", // code
        "cos", // character
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        cos_delta,
        NULL, // check func
        SINGLE_CHARACTER
    );
    
    // tan(x)
    struct delta_xy* tan_delta = delta_xy_create_first(15, 0, MP_DEFAULT_START_HEIGHT);
    math_structure_blueprint_set_append(
        msbs,
        "Tan Function", // name
        "\\tan", // code
        "tan", // character
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        tan_delta,
        NULL, // check func
       SINGLE_CHARACTER
    );

    // ln(x)
    struct delta_xy* ln_delta = delta_xy_create_first(10, 0, MP_DEFAULT_START_HEIGHT);
    math_structure_blueprint_set_append(
        msbs,
        "Natural Log Function", // name
        "\\ln", // code
        "ln", // character
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        ln_delta,
        NULL, // check func
        SINGLE_CHARACTER
    );

    // Exponent
    struct delta_xy* exponent_delta = delta_xy_create_first(0, 0, MP_DEFAULT_START_HEIGHT);
    delta_xy_append(exponent_delta, 5, -5, MP_DEFAULT_START_HEIGHT);
    math_structure_blueprint_set_append(
        msbs,
        "Exponential Function", // name
        "\\exp", // code
        "", // character
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        exponent_delta,
        NULL, // check func
        SINGLE_CHARACTER
    );

    // Integral (upper bound, lower bound, inside, integrating variable)
    struct delta_xy* integral_delta = delta_xy_create_first(5, 0, MP_DEFAULT_START_HEIGHT);
    delta_xy_append(integral_delta, 5, 20, MP_DEFAULT_START_HEIGHT);
    delta_xy_append(integral_delta, 10, -10, MP_DEFAULT_START_HEIGHT);
    delta_xy_append(integral_delta, 5, 0, MP_DEFAULT_START_HEIGHT);
    math_structure_blueprint_set_append(
        msbs,
        "Integral Structure", // name
        "\\int", // code
        "\xCA\x83", // character
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        integral_delta,
        NULL, // check func
        SINGLE_CHARACTER
    );

    // Derivative (deriving variable, expression)

    // Fraction (Numerator, Denominator)

    // Open Bracket
    struct delta_xy* open_bracket_delta = delta_xy_create_first(5, 0, MP_DEFAULT_START_HEIGHT);
    delta_xy_append(open_bracket_delta, 10, 0, MP_DEFAULT_START_HEIGHT);
    math_structure_blueprint_set_append(
        msbs,
        "Open Bracket", // name
        "(", // code
        "(", // character
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        open_bracket_delta,
        NULL, // check func
        SINGLE_CHARACTER
    );
    
    // Close Bracket
    math_structure_blueprint_set_append(
        msbs,
        "Close Bracket", // name
        ")", // code
        ")", // character
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        NULL,
        NULL, // check func
        SINGLE_CHARACTER
    );

    // Variable 
    math_structure_blueprint_set_append(
        msbs,
        "Variable", // name
        "\\variable",
        "",
        MP_DEFAULT_START_WIDTH,
        MP_DEFAULT_START_HEIGHT,
        NULL,
        cf_alphabetic_singular, // check func
        ALPHABETIC
    );

    // Nesting Bracket Expression Open
    struct delta_xy* open_paranthesis_delta = delta_xy_create_first(5, 0, MP_DEFAULT_START_HEIGHT);
    delta_xy_append(open_paranthesis_delta, 10, 0, MP_DEFAULT_START_HEIGHT);
    math_structure_blueprint_set_append(
        msbs,
        "Open Nest", // name 
        "{",  // code
        "", // character
        MP_DEFAULT_START_WIDTH, 
        MP_DEFAULT_START_HEIGHT,
        open_paranthesis_delta, // delta
        NULL, // check func
        SINGLE_CHARACTER
    );

    // Nesting Bracket Expression Close
    struct delta_xy* close_paranthesis_delta = delta_xy_create_first(5, 0, MP_DEFAULT_START_HEIGHT);
    delta_xy_append(close_paranthesis_delta, 10, 0, MP_DEFAULT_START_HEIGHT);
    math_structure_blueprint_set_append(
        msbs, 
        "Close Nest", // name
        "}",  // code
        "", // character
        MP_DEFAULT_START_WIDTH, 
        MP_DEFAULT_START_HEIGHT,
        close_paranthesis_delta, // delta
        NULL, // check func
        SINGLE_CHARACTER
    );

    printf("Number of msbs->msb_i is %d\n", msbs->msb_i);

    if (TEST_MMSBSD) 
    for (int i = 0; i < msbs->msb_i; i++) {
        math_structure_blueprint_t* msb = &(msbs->msb_arr[i]);
        printf("Is msb %d, NULL %s\n", i, msb == NULL ? "YES" : "NO");
        printf("Is msb->item_delta_set %d, NULL %s\n", i, msb->item_delta_set == NULL ? "YES" : "NO");
        delta_xy_t* dxy = msb->item_delta_set;
        if (msb != NULL && dxy != NULL) {
            printf("%d:", i); 
            printf(" name: \"%s\"", MSBSD_NULL_TO_STRING(msb->name)); 
            printf(" code=\"%s\"", MSBSD_NULL_TO_STRING(msb->code)); 
            printf(" character=\"%s\"\n", MSBSD_NULL_TO_STRING(msb->character));
            
            if (0 && dxy != NULL) {
                printf("\tchild count:%d\n", dxy == NULL ? 0 : dxy->length);
                printf("\t"); 
                for (int i1 = 0; i1 < dxy->length; i1++) {
                    printf(
                        "(%d, %d, %d), ", 
                        dxy->dx[i1], 
                        dxy->dy[i1], 
                        dxy->height[i1]
                    );
                }
                printf("\n"); 
            }
        } else {
            printf("bar\n");
        }
    }
    
    return msbs;
} 

// void math_structure_blueprint_set_free(math_structure_blueprint_set_t* msbs) {
//     for (int i = 0; i < msbs->msb_i; i++) {
//         math_structure_blueprint_free(&(msbs->msb_arr[i]));
//     }
    
//     free(msbs->msb_arr);
//     free(msbs);
// }

math_structure_blueprint_set_t* math_structure_blueprint_set_create() {
    math_structure_blueprint_set_t* msbs = malloc(sizeof(math_structure_blueprint_set_t));
    msbs->msb_arr = NULL;
    msbs->msb_i = 0;
    msbs->msb_size = 0;
    return msbs;
}

struct delta_xy* delta_xy_create_4(
    int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4
) {
    struct delta_xy* delta_grand = malloc(sizeof(struct delta_xy));
    delta_grand->length = 4;
    delta_grand->dx = calloc(4, sizeof(int));
    delta_grand->dy = calloc(4, sizeof(int));
    delta_grand->height = calloc(4, sizeof(int));

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
    msb->name = NULL;
    // msb->paint_box = paint_box;
    // msb->no_item = no_item;
    msb->start_width = start_width;
    msb->start_height = start_height;
    msb->item_delta_set = items_relevant;
    return msb;
}




void math_structure_blueprint_copy(
    math_structure_blueprint_t* msb_store, math_structure_blueprint_t* msb_source
) {
    msb_store->code             = msb_source->code;
    msb_store->character        = msb_source->character;
    msb_store->name             = msb_source->name;
    // msb_store->paint_box        = msb_source->paint_box;
    msb_store->start_width      = msb_source->start_width;
    msb_store->start_height     = msb_source->start_height;
    // msb_store->no_item          = msb_source->no_item;
    msb_store->item_delta_set   = msb_source->item_delta_set;
    msb_store->special          = msb_source->special;
}

// void math_structure_blueprint_free(math_structure_blueprint_t* msb) {
//     if (msb->code != NULL) free(msb->code);
//     if (msb->character != NULL) free(msb->character);
//     if (msb->name != NULL) free(msb->name);
//     free(msb->item_delta_set->dx);
//     free(msb->item_delta_set->dy);
//     free(msb->item_delta_set->height);
//     free(msb->item_delta_set);
// }

static char* safe_strdup(const char* s) {
    if (!s) return NULL;
    char* out = malloc(strlen(s) + 1);
    if (!out) return NULL;
    strcpy(out, s);
    return out;
}

// #define MSBSA_set_copy_string(variable, fieldname) \
// variable->fieldname = malloc(sizeof(char) * (strlen(fieldname) + 1)); \
// strcpy(variable->fieldname, fieldname); 

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
    CHECK_FUNC_T check_func,
    enum character_check special
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

    // Blueprint ptr
    math_structure_blueprint_t* msb = &(msbs->msb_arr[msbs->msb_i]);

    // Name, Code and Character
    msb->name = safe_strdup(name);
    msb->code = safe_strdup(code);
    msb->character = safe_strdup(character);

    // Dimensions
    msb->start_height = start_height;
    msb->start_width = start_width;
    
    // Items count is in the item delta
    // msb->item_count = (int) (sizeof(item_delta_set) / sizeof(struct delta_xy));
    msb->item_delta_set = item_delta_set;
    
    // Check Function
    msb->check_func = check_func;

    // Special
    msb->special = special;
    printf("Printing Special %s %d\n", msb->code, msb->special);


    msbs->msb_i++;
}

void math_structure_blueprint_set_test_print(
    math_structure_blueprint_set_t* msbs
) {
    printf("Mathematical Structure Blueprint set\n"); 
    printf("\tno_elements: %d\n", msbs->msb_i);
    printf("\n");
    if (msbs->msb_arr != NULL)
    for (int i = 0; i < msbs->msb_i; i++) {
        printf("%d:\n", i);
        printf("\tcode=%s\n", msbs->msb_arr[i].code);
        printf("\tcharacter=%s\n", msbs->msb_arr[i].character);
        // printf("\tpaint_box=%d\n", msbs->msb_arr[i].paint_box);
        printf("\tstart_height=%d\n", msbs->msb_arr[i].start_height);
        printf("\tstart_width=%d\n", msbs->msb_arr[i].start_width);
        if(msbs->msb_arr[i].item_delta_set != NULL)
        printf("\titem length=%d\n", msbs->msb_arr[i].item_delta_set->length);
        if(msbs->msb_arr[i].item_delta_set != NULL)
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
    math_structure_blueprint_t* msb = NULL;
    delta_xy_t* xy = NULL;
    for (int i = 0; i < msbs->msb_i; i++) {
        // for (int i2 = 0; i2 < msbs->msb_arr[i].item_delta_set->length; i2++) {
        msb = &(msbs->msb_arr[i]);
        xy = msb->item_delta_set;
        if (xy != NULL) {
            free(xy->dx);
            free(xy->dy);
            free(xy->height);
            free(xy);
            msb->item_delta_set = NULL;
        }
        
        if (msb->name != NULL)              free(msb->name);
        if (msb->code != NULL)              free(msb->code);
        if (msb->character != NULL)         free(msb->character);
        if (msb->item_delta_set != NULL)    free(msb->item_delta_set);
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