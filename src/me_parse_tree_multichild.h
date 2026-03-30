#ifndef ME_PARSE_TREE_MULTICHILD_H
#define ME_PARSE_TREE_MULTICHILD_H

#include "me_structure_blueprint.h"

/**
 * Type of Questions: or node type
 */
// enum MEPTM_TYPE {
//     SINGLE_CHARACTER,
//     NUMERIC,
//     ALPHABETIC,
//     ALPHANUMERIC,
// };


int is_alphabetic(char c);
int is_numeric(char c);

/**
 * Multi Child Parse tree needs a head, node count.
 */
typedef struct mcp_tree {
    struct mcp_node** head_arr;
    int head_i;
    int head_len;
    int node_count;
} mcp_tree_t;

/**
 * Needs a type of question,
 */
typedef struct mcp_node {
    enum special_structure type;
    char c; 
    int id;
    int child_len;
    int child_i;
    struct mcp_node** child_arr;
} mcp_node_t;

int mcp_tree_parse_code(
    mcp_tree_t* mcpt,
    char* code
);
int mcp_node_parse_code(
    mcp_node_t* node,
    char* code,
    int code_i,
    int code_len
);


mcp_tree_t* mcp_tree_create();

mcp_tree_t* mcp_tree_create_from_blueprint(
    math_structure_blueprint_set_t* msbs
);

mcp_node_t* mcp_tree_append_recursive();

void mcp_tree_free(mcp_tree_t* pt);


mcp_node_t* mcp_node_create_leaf(
    enum special_structure type,
    char c,
    int id
);

void mcp_node_free(mcp_node_t* pn);

mcp_node_t** mcp_node_create_new_arr(int* len, int *i, mcp_node_t** old_arr);

#endif