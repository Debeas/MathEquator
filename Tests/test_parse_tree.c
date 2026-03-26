/**
 * Testing file for parse tree to see if it recognizes the right stuff
 */
   
#include "..\me_parse_tree.h"
#include "..\me_structure_blueprint.h"

// Tests
int test_parse_tree_create_free();
int test_parse_tree_test_id_check_single_character();


int main(int argc, char *argv[]) {
    printf("Begin testing\n");
    test_parse_tree_create_free();
    test_parse_tree_test_id_check_single_character();
}

/**
 * Having a bug with the freeing of the math structure blueprint, unknown reason
 * I believe it is that some values are set NULL. I am checking 
 * TODO: fix bug 
 */
int test_parse_tree_create_free() {
    printf("Begin testing Parse Tree Create Free\n");
    math_structure_blueprint_set_t* msbs = math_structure_blueprint_set_defining();    
    parse_tree_t* pt = me_parse_tree_create_from_blueprint_set(msbs);
    
    me_parse_tree_free(pt);
    math_structure_blueprint_set_free(msbs);
    printf("End testing Parse Tree Create Free\n");
    return 1;
}

#define TPT_SINGLE_CHARACTER(character, id, val) \
int id = me_parse_tree_find(pt, character, 2); \
printf("Testing %s character to be %d it was %d\n", character, val, id); 

/**
 * Issue in identifyuing the id of the single character is not the being set 
 * properly.
 */
int test_parse_tree_test_id_check_single_character() {

    printf("\n////////////////////////////////////////////////////////////////////////////////\n");
    
    printf("Begin testing Parse Tree Single Character\n");
    math_structure_blueprint_set_t* msbs = math_structure_blueprint_set_defining();    
    parse_tree_t* pt = me_parse_tree_create_from_blueprint_set(msbs);
    
    TPT_SINGLE_CHARACTER("{", id_0, 1)
    TPT_SINGLE_CHARACTER("}", id_1, 1)
    TPT_SINGLE_CHARACTER("(", id_2, 1)
    TPT_SINGLE_CHARACTER(")", id_3, 1)

    me_parse_tree_free(pt);
    math_structure_blueprint_set_free(msbs);
    printf("End testing Parse Tree Single Character\n");
    return 1;
}