/**
 * Parse tree with multiple children
 *  - Take a list of item
 */

#include "me_trie.h"
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
            return mcp_node_parse_code(mcpt->head_arr[i_head], code, 1, strlen(code));
        }
    }
    return character_check_set_parse(mcpt->cc, code);

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
    mcpt->cc = character_check_set_create();
    return mcpt;
}

/**
 * Errors in this function
 */
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

        if (TEST_MPTM) 
        printf("Beginning insert of %s to the trie\n", cur->name);
            
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
                while (mcpt->head_i >= mcpt->head_len) {
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
                // cur->special,
                id,
                mcpt->head_arr[head_i]
            );
        } else {
            character_check_set_set(mcpt->cc, cur->special, id);    
            printf("for id: %d, special: %d and %s\n", id, cur->special, cur->code);
        }
    }
    return mcpt;
}

/**
 * Used to be called at every new index
 * 
 * Adding nodes to the trie every time there is node or letter that is not there.
 * 
 * Special Nodes are differently treated and are always just checked once then 
 * they are correct. 
 * 
 * Return:
 *  - Is the head of the tree 
 */
mcp_node_t* mcp_tree_append_recursive(
    int code_i,
    int code_len,
    char* code,
    // enum special_structure special,
    int id,
    mcp_node_t* node
) {
    int found_flag = FALSE;


    if (TEST_MPTM) {
        if (node == NULL) 
        printf("Node is NULL\n");
        printf("node: %d\n", node);
        printf("node->child_len: %d\n", node->child_len);
        printf("node->child_i: %d\n", node->child_i);
    }


    

    // Check if the node is normal
    for (int i_child = 0; i_child < node->child_i; i_child++) {
        // Check the single character
        if (
            code_i < code_len &&
            // special == SINGLE_CHARACTER &&
            code[code_i] == node->child_arr[i_child]->c
        ) {
            // Found node now check if it is terminal
            if (code_len == 1 + code_i && node->child_arr[i_child]->id == -1) {
                // Node is terminal
                node->child_arr[i_child]->id = id;
                return node;
            } else {   
                // Node is not terminal
                return mcp_tree_append_recursive(code_i + 1, code_len, code, id, (node->child_arr[i_child]));
            }
        }
    }

    // Create new a child node
    if (TEST_MPTM)
    printf("Creating a new child node, depth: %d, char: %c\n", code_i, node->c);

    while (node->child_len == 0 || node->child_i + 1 >= node->child_len) {

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
    if (code_i < code_len) {
        mcp_node_t* new_child = mcp_node_create_leaf(
            code[code_i],
            (code_len == code_i + 1 ? id : -1)
        );

       node->child_arr[node->child_i++] = new_child;

        return mcp_tree_append_recursive(
            code_i + 1, code_len, code, id, new_child
        );
    } else {
        return node;
    }
}

mcp_node_t** mcp_node_create_new_arr(int* len, int *i, mcp_node_t** old_arr) {
    (*len) = ((*len) == 0 ? 2 : 2 * (*len));
    mcp_node_t** new_arr = calloc((*len), sizeof(mcp_node_t*));
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
    if (TEST_MPTM)
    printf("Creating Leaf %c %d\n", c, id);

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
    character_check_set_free(mcpt->cc);
    free(mcpt);
}

void mcp_node_free(mcp_node_t* pn) {
    for (int i = 0; i < pn->child_i; i++) {
        mcp_node_free(pn->child_arr[i]);
    }
    if (pn->child_arr != NULL) free(pn->child_arr);
    free(pn);
}

int is_numeric(char c) {
    return ('0' <= c && c <= '9');
}

int is_alphabetic(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}