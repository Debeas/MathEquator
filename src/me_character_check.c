#include "me_character_check.h"
#include <stdlib.h>

#define TEST_CHARACTER_CHECK 0

character_check_set_t* character_check_set_create() {
    character_check_set_t* ccs = malloc(sizeof(character_check_set_t));
    ccs->len = 3;
    ccs->arr = (int*) calloc(ccs->len, sizeof(int));
    ccs->arr[0] = -1;
    return ccs;
}

void character_check_set_free(character_check_set_t* ccs) {
    free(ccs->arr);
    free(ccs);
}

int character_check_set_parse(character_check_set_t* ccs, char* code) {
    int i = 0;
    int flag_numeric = 1;
    int flag_alphabetic = 1;
    while (code[i] != '\0') {
        if (
            !('a' <= code[i] && code[i] <= 'z') &&
            !('A' <= code[i] && code[i] <= 'Z') 
        ) {
            if (TEST_CHARACTER_CHECK)
            printf("not alphabetic on %d\n", i);
            flag_alphabetic = 0;
        }
        if (!('0' <= code[i] && code[i] <= '9')) {
            if (TEST_CHARACTER_CHECK)
            printf("not numeric on %d\n", i);
            flag_numeric = 0;
        }
        i++;
    }
    
    if (flag_alphabetic == 1) {
        if (TEST_CHARACTER_CHECK)
        printf("Is alphabetic %d\n", ccs->arr[ALPHABETIC]);
        return ccs->arr[ALPHABETIC];
    }
    if (flag_numeric == 1) {
        if (TEST_CHARACTER_CHECK)
        printf("Is numeric %d\n", ccs->arr[NUMERIC]);
        return ccs->arr[NUMERIC];
    } 
    return -1;
}

void character_check_set_set(character_check_set_t* ccs, int cc, int id) {
    if (0 <= cc && cc < ccs->len) {
        if (TEST_CHARACTER_CHECK)
        printf("Set cc %d %d\n", cc, id);
        ccs->arr[cc] = id;
    } else {
        if (TEST_CHARACTER_CHECK)
        printf("Failed Set cc %d %d\n", cc, id);
    }
}
