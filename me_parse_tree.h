#ifndef ME_PARSE_TREE_H

/**
 * Ensuring that both are not defined. 
 */
#ifndef ME_PARSE_TREE_MULTICHILD_H
#define ME_PARSE_TREE_H

#include "me_structure_blueprint.h"

// enum MEPT_QUESTION_TYPE{
//     SINGLE_CHARACTER,
//     NUMERIC,
//     ALPHABETIC,
//     ALPHANUMERIC,
// };

typedef struct parse_tree {
    int total_questions;
    int next_id;
    struct question* first_question;
} parse_tree_t;

typedef struct question {
    enum special_structure type;
    int answer_id;
    char c;

    // Tree
    struct question* question_true;
    struct question* question_false;
} question_t;


int me_parse_tree_find(parse_tree_t* pt, char* code, int code_len);
int me_parse_tree_find_recurse(question_t* q, char* code, int code_i, int code_len);

parse_tree_t* me_parse_tree_create_from_blueprint_set(
    math_structure_blueprint_set_t* msbs
);

void me_parse_tree_print(parse_tree_t* pt);
void me_parse_tree_free(parse_tree_t* pt);
void me_parse_tree_append(
    parse_tree_t* mept, 
    char* code, 
    int id, 
    enum special_structure special
);

question_t* question_create(enum MEPT_QUESTION_TYPE type, int id, char c);

void question_free(question_t* q);
int question_ask(question_t* cur, char c);


#endif
#endif