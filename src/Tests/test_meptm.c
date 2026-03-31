#include <stdio.h>
#include "..\me_parse_tree_multichild.h"

void test_create_free();
void test_id_of_open_parenthesis();
void test_print_out();
void test_print_out_recursive(mcp_node_t* mcpn, int n);

int main() {
    test_create_free();
    test_id_of_open_parenthesis();
    test_print_out();
}

/**
 * Test Create and then free
 */
void test_create_free() {
    printf("\nBeginning test create and free\n");
    mcp_tree_t* w = mcp_tree_create_from_blueprint(math_structure_blueprint_set_defining());
    mcp_tree_free(w);
    printf("Ending test create and free\n");
}

/**
 * Test that '{' is in 
 */
void test_id_of_open_parenthesis() {
    printf("\nBeginning test id of of open parenthesis\n");
    mcp_tree_t* w = mcp_tree_create_from_blueprint(math_structure_blueprint_set_defining());
    
    // Test code
    int id = mcp_tree_parse_code(w, "\\int");
    printf("id is %d\n", id);
    
    mcp_tree_free(w);
    printf("Ending test id of of open parenthesis\n");
}

void test_print_out() {
    printf("\nBeginning test of print out tree\n"); 
    
    // Create
    mcp_tree_t* w = mcp_tree_create_from_blueprint(math_structure_blueprint_set_defining());
    
    // Recurse
    printf("\tBegin with head_i: %d\n", w->head_i);
    for (size_t i = 0; i < w->head_i; i++) {
        test_print_out_recursive(w->head_arr[i], 0);
    }

    // free
    mcp_tree_free(w);
    
    printf("Ending test of print out tree\n"); 
}

void test_print_out_recursive(mcp_node_t* mcpn, int n) {
    for (int i = 0; i < n; i++) putc(' ', stdout);
    printf("c: %c, id: %d \n", mcpn->c,  mcpn->id);
    
    for (int i = 0; i < mcpn->child_i; i++) {
        test_print_out_recursive(mcpn->child_arr[i], n + 1);
    }
    
}
