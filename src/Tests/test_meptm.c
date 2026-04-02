#include <stdio.h>
#include <assert.h>
#include "..\me_parse_tree_multichild.h"

void test_create_free();
void test_id_of_open_parenthesis();
void test_print_out();
void test_print_out_recursive(mcp_node_t* mcpn, int n);
void test_mcp_tree_create();
void test_mcp_tree_create_and_free();
void test_mcp_node_create_leaf();


/* -------------------------------------------------------------------------- */

static int tests_run = 0;
static int tests_passed = 0;

// Copied Claude's code
#define TEST(name) \
do { printf("\n[TEST] %s\n", name); } while(0)

#define TEST_FINISH(name) \
do { printf("\n[TEST_FINISH] %s\n", name); } while(0)

#define EXPECT(cond) \
do { \
    tests_run++; \
    if (cond) { \
        printf("  PASS: %s\n", #cond); \
        tests_passed++; \
    } else { \
        printf("  FAIL: %s  (line %d)\n", #cond, __LINE__); \
    } \
} while(0)

/* -------------------------------------------------------------------------- */

int main() {
    test_print_out();
    
    test_mcp_node_create_leaf();
    test_mcp_tree_create_and_free();

    test_create_free();
    test_id_of_open_parenthesis();

    printf("Tests passed: %d/%d\n", tests_passed, tests_run);
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
    
    EXPECT(mcp_tree_parse_code(w, "\\blank") == 0);
    EXPECT(mcp_tree_parse_code(w, "\\sin") == 1);
    EXPECT(mcp_tree_parse_code(w, "\\cos") == 2);
    EXPECT(mcp_tree_parse_code(w, "\\tan") == 3);
    EXPECT(mcp_tree_parse_code(w, "\\ln") == 4);
    EXPECT(mcp_tree_parse_code(w, "\\exp") == 5);
    EXPECT(mcp_tree_parse_code(w, "\\int") == 6);
    EXPECT(mcp_tree_parse_code(w, "(") == 7);
    EXPECT(mcp_tree_parse_code(w, ")") == 8);
    EXPECT(mcp_tree_parse_code(w, "asdsa") == 9);
    EXPECT(mcp_tree_parse_code(w, "{") == 10);
    EXPECT(mcp_tree_parse_code(w, "}") == 11);
    printf("id is %d\n", id);
    
    mcp_tree_free(w);
    printf("Ending test id of of open parenthesis\n");
}

void test_print_out() {
    TEST("Print out");
    
    // Create
    mcp_tree_t* w = mcp_tree_create_from_blueprint(math_structure_blueprint_set_defining());
    

    // Recurse
    printf("\tBegin with head_i: %d\n", w->head_i);
    for (size_t i = 0; i < w->head_i; i++) {
        test_print_out_recursive(w->head_arr[i], 0);
    }
    
    // free
    mcp_tree_free(w);
    
    TEST_FINISH("Print out");
    
}

void test_print_out_recursive(mcp_node_t* mcpn, int n) {
    for (int i = 0; i < n; i++) printf(" ");
    printf("c: %c, id: %d \n", mcpn->c,  mcpn->id);
    
    for (int i = 0; i < mcpn->child_i; i++) {
        test_print_out_recursive(mcpn->child_arr[i], n + 1);
    }
    
}

/**
 *   
 */
void test_mcp_tree_create_and_free() {
    TEST("mcp_tree_create");

    mcp_tree_t* mcpt = mcp_tree_create();
    
    EXPECT(mcpt->head_arr == NULL);
    EXPECT(mcpt->head_i == 0);
    EXPECT(mcpt->head_len == 0);
    EXPECT(mcpt->node_count == 0);
    
    mcp_tree_free(mcpt);
    
    mcpt = NULL;

    EXPECT(mcpt == NULL);

}

void test_mcp_node_create_leaf() {
    TEST("Mcp_node_t");
    mcp_node_t* n = mcp_node_create_leaf('{', 2);

    EXPECT(n->child_i == 0);
    EXPECT(n->child_len == 0);
    EXPECT(n->child_arr == NULL);
    EXPECT(n->id == 2);
    EXPECT(n->c == '{');

    mcp_node_free(n);
    // free(n);

}