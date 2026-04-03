#ifndef ME_PARSE_TREE_MULTICHILD_H
#define ME_PARSE_TREE_MULTICHILD_H

#include "me_structure_blueprint.h"
#include "me_character_check.h"
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
typedef struct mcp_trie {
    struct mcp_node** head_arr;
    int head_i;
    int head_len;
    int node_count;
    struct character_check_set* cc;
} mcp_trie_t;

/**
 * Needs a type of question,
 */
typedef struct mcp_node {
    // enum special_structure type;
    char c; 
    int id;
    int child_len;
    int child_i;
    struct mcp_node** child_arr;
} mcp_node_t;

int mcp_trie_parse_code(
    mcp_trie_t* mcpt,
    char* code
);
int mcp_node_parse_code(
    mcp_node_t* node,
    char* code,
    int code_i,
    int code_len
);


mcp_trie_t* mcp_trie_create();

mcp_trie_t* mcp_trie_create_from_blueprint(
    math_structure_blueprint_set_t* msbs
);

mcp_node_t* mcp_trie_append_recursive(
    int code_i,
    int code_len,
    char* code,
    // enum special_structure special,
    int id,
    mcp_node_t* node
);

void mcp_trie_free(mcp_trie_t* pt);


mcp_node_t* mcp_node_create_leaf(
    // enum special_structure type,
    char c,
    int id
);

void mcp_node_free(mcp_node_t* pn);

mcp_node_t** mcp_node_create_new_arr(int* len, int *i, mcp_node_t** old_arr);

#endif