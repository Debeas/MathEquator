#ifndef ME_PARSE_TREE_MULTICHILD_H
#define ME_PARSE_TREE_MULTICHILD_H

#include "me_structure_blueprint.h"

/**
 * Type of Questions: or node type
 */
enum MEPTM_TYPE {
    SINGLE_CHARACTER,
    NUMERIC,
    ALPHABETIC,
    ALPHANUMERIC,
};

/**
 * Parse tree needs a head, node count.
 */
typedef struct parse_tree {
    struct parse_node* head;
    int node_count;
} parse_tree_t;

/**
 * Needs a type of question,
 */
typedef struct parse_node {
    enum MEPTM_TYPE type;
    char c; 
    int id;
    int child_len;
    struct parse_node** child_arr;
} parse_node_t;


parse_tree_t* parse_tree_create_from_blueprint(
    math_structure_blueprint_set_t* msbs
);
parse_node_t* parse_tree_create_recursive();
void parse_tree_free(parse_tree_t* pt);


parse_node_t* parse_node_create_leaf(
    enum MEPTM_TYPE type,
    char c,
    int id
);
void parse_node_free(parse_node_t* pn);

#endif