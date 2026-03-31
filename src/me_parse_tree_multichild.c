/**
 * Parse tree with multiple children
 *  - Take a list of item
 */

#include "me_parse_tree_multichild.h"
#include "me_structure_blueprint.h"

#define TEST_MPTM 0


int mcp_tree_parse_code(
    mcp_tree_t* mcpt,
    char* code
) {

    for (int i_head = 0; i_head < mcpt->head_i; i_head++) {

        // Single Character
        if (
            // mcpt->head_arr[i_head]->type == SINGLE_CHARACTER &&
            code[0] == mcpt->head_arr[i_head]->c
        ) {
            return mcp_node_parse_code(mcpt->head_arr[i_head], code, 0, strlen(code));
        }
    }

    return -1;
}

int mcp_node_parse_code(
    mcp_node_t* node,
    char* code,
    int code_i,
    int code_len
) {

    if (code_i == code_len) {
        return node->id;
    }

    for (int i_child = 0; i_child < node->child_i; i_child++) {
        
        // Single Character
        if (
            // node->child_arr[i_child]->type == SINGLE_CHARACTER &&
            code[code_i] == node->child_arr[i_child]->c
        ) {
            return mcp_node_parse_code(node->child_arr[i_child], code, code_i + 1, code_len);
        }
    }

    return -1;
}

mcp_tree_t* mcp_tree_create() {
    mcp_tree_t* mcpt = malloc(sizeof(mcp_tree_t));
    mcpt->node_count = 0;
    mcpt->head_len = 0;
    mcpt->head_i = 0;
    mcpt->head_arr = NULL;
    return mcpt;
}

mcp_tree_t* mcp_tree_create_from_blueprint(
    math_structure_blueprint_set_t* msbs
) {
    mcp_tree_t* mcpt = mcp_tree_create();
    mcpt->head_arr = NULL;
    mcpt->head_i = 0;
    mcpt->head_len = 0;
    mcpt->node_count = 0;


    int head_i = -1;
    math_structure_blueprint_t* cur = NULL;
    for (int id = 0; id < msbs->msb_i; id++) {
        int code_len = strlen(msbs->msb_arr[id].code);
        cur = &(msbs->msb_arr[id]);
            
        // Finding head i
        if (cur->special == SINGLE_CHARACTER) {
            printf("Is it a singlen character i:%d  and \"%s\"\n", id, cur->code);

            head_i = -1;
            if (mcpt->head_i >= 1) 
            for (int head_in = 0; head_in < mcpt->head_i; head_in++) {
                if (
                    mcpt->head_arr[head_in]->c == cur->code[0] 
                ) {
                    head_i = head_in;
                }    
            }
        
            // The create new head node
            if (head_i == -1) {
                if (mcpt->head_i == mcpt->head_len) {
                    mcp_node_t** new_arr = malloc(sizeof(mcp_node_t*));
                    mcpt->head_arr = mcp_node_create_new_arr(&(mcpt->head_len), &(mcpt->head_i), mcpt->head_arr);
                        
                }
                head_i = mcpt->head_i;
                mcpt->head_arr[mcpt->head_i++] = mcp_node_create_leaf(cur->code[0], (code_len == 1 ? id : -1));
            } 
                
            if (TEST_MPTM) {
                printf("mcpt->node_count: %d, \n", mcpt->node_count);
                printf("mcpt->Head_len: %d, \n", mcpt->head_len);
                printf("mcpt->Head_i: %d, \n", mcpt->head_i);
                printf("head_i: %d, \n", head_i);
            }
            if (head_i > -1) mcp_tree_append_recursive(
                1, 
                strlen(cur->code), // calculates the length of the string excluding null-termination
                cur->code,
                cur->special,
                id,
                mcpt->head_arr[head_i]
            );
        } else printf("for id: %d, special: %d and %s\n", id, cur->special, cur->code);
    }
    return mcpt;
}

/**
 * Used to be called at every new index
 * 
 * Special Nodes are differently treated and are always just checked once then 
 * they are correct. 
 * 
 * Return:
 *  - Is the head of the tree 
 */
mcp_node_t* mcp_tree_append_recursive(
    int i,
    int code_len,
    char* code,
    // enum special_structure special,
    int id,
    mcp_node_t* node
) {
    int found_flag = FALSE;

    if (TEST_MPTM) {
        printf("node: %d\n", node);
        printf("node->child_len: %d\n", node->child_len);
        printf("node->child_i: %d\n", node->child_i);
    }

    // Check if the node is normal
    if (node->child_len > 0) for (int i_child = 0; i_child < node->child_len; i_child++) {


        // Check the single character
        if (
            i < code_len &&
            // special == SINGLE_CHARACTER &&
            code[i] == node->child_arr[i_child]->c
        ) {
            if (code_len == 1 + i && node->child_arr[i_child]->id == -1) {
                node->child_arr[i_child]->id = id;
            }
            return mcp_tree_append_recursive(i + 1, code_len, code, id, (node->child_arr[i_child]));
        }
    }

    // Create new 
    if (TEST_MPTM)
    printf("Error going to be caused.\n");
    if (node->child_i + 1 >= node->child_len) {

        // Create new array
        node->child_arr = mcp_node_create_new_arr(&(node->child_len), &(node->child_i), node->child_arr);

        // Thing
        if (TEST_MPTM) {
            printf("Error going to be caused. length: %d\n", node->child_len);
            printf("node->child_len: %d\n", node->child_len);
            printf("node->child_i: %d  \n", node->child_i);
        }

    }

    // Add end
    if (i < code_len) {
    mcp_node_t* new_child = mcp_node_create_leaf(
        code[i],
        (code_len == i + 1 ? id : -1)
    );

    node->child_arr[node->child_i++] = new_child;

        return mcp_tree_append_recursive(
            i + 1, code_len, code, id, new_child
        );
    } else return node;
}

mcp_node_t** mcp_node_create_new_arr(int* len, int *i, mcp_node_t** old_arr) {
    (*len) = ((*len) == 0 ? 2 : 2 * (*len));
    mcp_node_t** new_arr = calloc(*len, sizeof(mcp_node_t*));
    for (int i_child = 0; i_child < (*i); i_child++) {
        new_arr[i_child] = old_arr[i_child];
    }
    free(old_arr);
    return new_arr;
}


mcp_node_t* mcp_node_create_leaf(
    // enum special_structure type,
    char c,
    int id
) {
    mcp_node_t* mcpn = malloc(sizeof(mcp_node_t));
    // mcpn->type = type;
    mcpn->c = c;
    mcpn->id = id;
    mcpn->child_i = 0;
    mcpn->child_len = 0;
    mcpn->child_arr = NULL;
    return mcpn;
}


void mcp_tree_free(mcp_tree_t* mcpt) {
    if (mcpt->head_arr != NULL) {
        for (int i = 0; i < mcpt->head_i; i++) {
            mcp_node_free(mcpt->head_arr[i]);
        }
        
        free(mcpt->head_arr);
    }
    free(mcpt);
}

void mcp_node_free(mcp_node_t* pn) {
    for (int i = 0; i < pn->child_i; i++) {
        mcp_node_free(pn->child_arr[i]);
    }
    free(pn->child_arr);
    
    free(pn);
}

int is_numeric(char c) {
    return ('0' <= c && c <= '9');
}

int is_alphabetic(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}