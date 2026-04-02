#ifndef CHARACTER_CHECK_H
#define CHARACTER_CHECK_H

/**
 * Isolating the character check into a thing. The hierarchy needs to be 
 * established as well.
 * 
 * Two things use this variables and numbers one has any use of digits and the 
 * other underscore and letters big or small
 * 
 */

typedef enum character_check {
    SINGLE_CHARACTER,
    ALPHABETIC,
    NUMERIC
} character_check_t;

typedef struct character_check_set {
    int* arr;
    int len;
} character_check_set_t;


character_check_set_t* character_check_set_create();
void character_check_set_free(character_check_set_t* ccs);
int character_check_set_parse(character_check_set_t* ccs, char* code);
void character_check_set_set(character_check_set_t* ccs, int cc, int id);



#endif