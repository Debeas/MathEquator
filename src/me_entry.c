// #include <windows.h>
// #include "me_paint.h"
// #include "me_structure.h"
#include "me_entry.h"
// #include "me_parse_tree.h"
#include <stdio.h>

#define TEST_TREE_NEXT_ITEM 1
#define TEST_ME_HANDLE 1
#define TEST_ME_EXTRACT_NEXT_WORD 1
#define TEST_MEDT_NEXT_ITEM_SET 1
/**
 *
 * Datatype to hold next request
 */

int not_bracket_parenthesis_brace_angles(char c);

/**
 * Bugs
 *  - [ ] button twice causes a problem
 */
void me_handle_2(HWND hwndCtrl, struct me_data_tree** ptr_data, math_structure_blueprint_set_t* msbs) {
    // Data Setup
    if (*ptr_data != NULL) {
        me_data_tree_free(*ptr_data);
    }
    *ptr_data = me_data_tree_create();
    me_data_tree_t* data = *ptr_data;

    if (data == NULL) {
        printf("Data is null\n");
    }

    // Buffer setup
    int buf_size = 100;
    char* buf = malloc(sizeof(char) * buf_size); 
    char* buf_nword = malloc(sizeof(char) * buf_size); 
    GetWindowText(hwndCtrl, buf, buf_size);

    // Finding Code 
    math_structure_blueprint_t* msb = NULL;
    math_structure_t* ms_cur = NULL;
    int target_i = -2;
    int buf_nword_len = -1;
    int shift_i = 0;

    // // Parse Tree
    // parse_tree_t* pt = me_parse_tree_create_from_blueprint_set(msbs);

    // Trie
    mcp_trie_t* mcpt = mcp_trie_create_from_blueprint(msbs);

    
    // Painting delta_location
    int cur_x = 0;
    int cur_y = 0;

    // Loop through text
    while (
        shift_i < buf_size && 
        0 < (buf_nword_len = me_extract_next_word(buf + shift_i, buf_size - shift_i, buf_nword, buf_size)) &&
        target_i == -2
    ) {
        // New Word Print
        if (TEST_ME_HANDLE)
        printf("New Word: %s at %d len %d\n", buf_nword, shift_i, buf_nword_len);
        
        // Find Codes loop through things
        // target_i = me_parse_tree_find(pt, buf_nword, buf_nword_len);
        target_i = mcp_trie_parse_code(mcpt, buf_nword); 
        msb = &(msbs->msb_arr[target_i]);

        // for (int i = 0; target_i == -1 && i < msbs->msb_i; i++) {
        //     if (strcmp(buf_nword, msbs->msb_arr[i].code) == 0) {
        //         target_i = i;
        //         msb = &(msbs->msb_arr[target_i]);
        //     }
        // } 

        // Add to tree
        if (target_i >= 0) {
            me_data_tree_next_item_set(data, msb, &ms_cur, buf_nword, buf_nword_len);
            
            // TEST Print
            if (TEST_ME_HANDLE)
            printf("found: %s at %d len %d\n", msb->code, shift_i, buf_nword_len);
        }


        // Iterate
        if (target_i != -1) target_i = -2;
        shift_i += buf_nword_len - 1;
    }

    if (TEST_ME_HANDLE) {
        printf("me_handle_2: buf = \"%s\" buf2 = \"%s\" len=%d shift_i:%d buf_size:%d target_i:%d \n", buf, buf_nword, buf_nword_len, shift_i, buf_size, target_i);
        printf(
            "End Condtion: %s\n",
            (
                !(shift_i < buf_size) ? "First" : 
                !(target_i == -2) ? "Third" : 
                "Second" 
            )
        );
    }

    free(buf_nword);
    free(buf);
}

void me_handle(HWND hwndCtrl, struct math_entry_data* data, math_structure_blueprint_set_t* msbs) {
    int DATA_NULL = data == NULL;

    // Buffer setup
    int buf_size = 100;
    char* buf = malloc(sizeof(char) * buf_size); 
    char* buf_2 = malloc(sizeof(char) * buf_size); 
    GetWindowText(hwndCtrl, buf, buf_size);

    // // Create Sturcture
    // math_structure_t* msb_head = NULL;

    // Finding Code
    int target_i = -2;
    int nword_len = -1;
    int shift_i = 0;

    // where to paint
    int cur_x;
    int cur_y;
    if (!DATA_NULL) {
        cur_x = data->start_x;
        cur_y = data->start_y;
    } else printf("Data is null\n");

    // Loop through text
    while (
        shift_i < buf_size && 
        0 < (nword_len = me_extract_next_word(buf + shift_i, buf_size - shift_i, buf_2, buf_size)) &&
        target_i == -2
    ) {
        // Find Codes
        target_i = -1;
        for (int i = 0; target_i == -1 && i < msbs->msb_i; i++) {
            if (strcmp(buf_2, msbs->msb_arr[i].code) == 0) {
                target_i = i;
            }
        } 

    // // Make a Item or Node
    // if (target_i == -1) {

    // }
        // New symbol>>>>>
        printf("Found symbol %s in %d %s \n", buf_2, target_i, msbs->msb_arr[target_i].character);

        // Adding a found Structure;
        if (target_i >= 0 && !DATA_NULL) {
            me_data_append(data, &(msbs->msb_arr[target_i]), cur_x, cur_y, NULL);
        }

        
        if (target_i != -1) target_i = -2;
        
        shift_i += nword_len;
    }

    if (TEST_ME_HANDLE)
    printf("buf = \"%s\" buf2 = \"%s\" len=%d\n", buf, buf_2, nword_len);

    free(buf_2);
    free(buf);
}


/**
 * This needs testing
 */
int me_extract_next_word(char* buf, int buf_size, char* nword, int nword_size) {
    
    // First Spaces
    int i = 0;
    while (i < buf_size && buf[i] == ' ') i++;

    // If bracket just added because of bracket thing.
    // Single Character word
    if (buf[i] == '(' || buf[i] == ')' || buf[i] == '{' || buf[i] == '}') {
        nword[0] = buf[i];
        nword[1] = '\0';
        return 2;
    }
    
    // First Spaces
    int nword_i = 0;
    while (
        i < buf_size && nword_i < nword_size && buf[i] != ' ' && 
        buf[i] != '\0' && not_bracket_parenthesis_brace_angles(buf[i])
    ) {
        nword[nword_i] =  buf[i];
        i++;
        nword_i++;
    }
    nword[nword_i] = '\0';
    nword_i++;
    
    // Very good
    if (nword_i >= 1) return nword_i;
    
    if (TEST_ME_EXTRACT_NEXT_WORD)  {
        printf("Failure of the nword\n");
        // nword[0] = '\0';
    } 

    return FALSE;

}

int not_bracket_parenthesis_brace_angles(char c) {
    return !(c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']');
}

 //|\   /|\   /|\   /|\   /|\   /|\   /|\   /|\   /|\   /|\   /|\   /|\   /|\   
 // \\ // \\ // \\ // \\ MATHEMATICS ENTRY // \\ // \\ // \\ // \\ // \\ // \\ /
//   \|/   \|/   \|/   \|/   \|/   \|/   \|/   \|/   \|/   \|/   \|/   \|/   \|/

#pragma region me data

me_data_t* me_data_create(int start_x, int start_y) {
    me_data_t* med = malloc(sizeof(me_data_t));
    med->i_request = 0;
    med->request_size = 0;
    med->start_x = start_x;
    med->start_y = start_y;
    med->requests = NULL;
    return med;
}

void me_data_free(me_data_t* med) {
    for (int i = 0; i < med->i_request; i++) {
        math_structure_free(med->requests[i]);
    }
    
    if (med->requests != NULL) free(med->requests);
    free(med);
}

/**
 * Math Entry data append
 */
void me_data_append(
    me_data_t* med, 
    math_structure_blueprint_t* msb, 
    int x, 
    int y, 
    math_structure_t** item_p_arr
) {
    // Structure is a list when it should be a tree
    math_structure_t* structure = math_structure_create(msb, x, y, item_p_arr);
    if (med->request_size == 0) {
        med->request_size = 1;
        med->requests = malloc(sizeof(math_structure_t*));
    } else if (med->i_request >= med->request_size) {

        med->request_size *= 2;
        math_structure_t** new_structure = malloc(med->request_size * sizeof(math_structure_t*));
        for (int i = 0; i < med->i_request; i++) {
            new_structure[i] = med->requests[i];
        }
        free(med->requests);
        med->requests = new_structure;
    }

    printf("New Structure to the med no. %d\n", med->i_request);


    med->requests[med->i_request++] = structure;
}

#pragma endregion me data

// Math Data Tree
////////////////////////////////////////////////////////////////////////////////

/**
 * Math entry data tree create 
 */
me_data_tree_t* me_data_tree_create() {
    me_data_tree_t* mdt = malloc(sizeof(me_data_tree_t));

    mdt->head = malloc(sizeof(math_structure_t));
    mdt->head_count = 1;
    mdt->new_head_flag = TRUE;
    mdt->start_x = 0;
    mdt->start_y = 0;

    return mdt;
}

/**
 * Math Entry data tree free
 */
me_data_tree_free(me_data_tree_t* medt) {
    if (medt->head_count != 0) {
        for (int i = 0; i < medt->head_count; i++) {
            math_structure_free(medt->head[i]);
        }
        free(medt->head);
    }
    free(medt);
}

/**
 * Math Entry add item structure where it is a root that is in to a tree and that 
 * it is one at a time, also moving the entry position based on the setting of 
 * the branch item and fillling out how many items it has,
 * 
 * x,y should be calculated based on width of the text or item 
 * 
 * Tree structure needs something that can handle items that have a symbol that 
 * begins after the first element such we need a way to add that in this
 *  - EBNF Structure
 */
void me_data_tree_next_item_set(
    me_data_tree_t* med,
    math_structure_blueprint_t* msb, // blueprint ptr
    math_structure_t** cur, 
    char* value,
    int value_len
) {

    

    // Shoud never occur
    if (med->head == NULL) {
        med->head = malloc(sizeof(math_structure_t)); 
        med->head_count = 1;
    }
        
    if (med->new_head_flag) {
        med->head[med->head_count - 1] = math_structure_create_childless(msb, 0, 0, value, value_len);
        (*cur) = med->head[med->head_count - 1];
        (*cur)->parent = NULL;
        
        med->new_head_flag = FALSE;
        
        if (TEST_MEDT_NEXT_ITEM_SET)
        printf("medt: new head set!\n");
        return;
    } else  {
        (*cur)->item_p_arr[(*cur)->next_item_i] = math_structure_create_childless(
            msb, 0,0, value, value_len
        );
        (*cur)->next_item_i++;
        if (TEST_MEDT_NEXT_ITEM_SET)
        printf("medt: Made a new structure\n");
        
        // Check if Cur needs to go up one
        while ((*cur)->next_item_i == (*cur)->no_item) {
            if ((*cur)->parent != NULL) {
                (*cur) = (*cur)->parent;
            } else  {
                // Hit the head with bad
                if (TEST_MEDT_NEXT_ITEM_SET)
                printf("medt: Extending Head with a new item\n");
                math_structure_t** ms_arr = malloc(sizeof(math_structure_t) * med->head_count++);
                for (int i = 0; i < med->head_count - 1; i++) {
                    ms_arr[i] = med->head[i];
                }
                med->new_head_flag = TRUE;
                med->head[med->head_count - 1] = NULL;
                (*cur) = med->head[med->head_count - 1];
            }
            if (TEST_MEDT_NEXT_ITEM_SET)
            printf("medt: up one!\n");
        }
    }


}



// Tools
////////////////////////////////////////////////////////////////////////////////
