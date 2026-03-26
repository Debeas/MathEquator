#include <stdlib.h>
#include "me_parse_tree.h"
#include "me_structure_blueprint.h"

#define ME_PARSE_TREE_CREATE_FROM_BLUEPRINT_SET 1
#define TEST_QUESTION_CREATE 0
#define TEST_ME_PARSE_TREE_APPEND 0
#define TEST_PARSE_TREE_APPEND 1
#define TEST_PARSE_TREE_FIND 1

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif
void me_parse_tree_print_question(question_t* q, int d, int answer);



/**
 * I need to find the id of the code. go through every node and check it is there
 * I need a way to check for alphanumeric things for the codes that are more 
 * complicated. 
 *  - [ ] Testing 
 * 
 */
int me_parse_tree_find(parse_tree_t* pt, char* code, int code_len) {
    int id = -1;

    // Empty return
    if (code_len == 0) return id;
    
    char c = code[0];
    return me_parse_tree_find_recurse(pt->first_question, code, 0, code_len);
}

int me_parse_tree_find_recurse(question_t* q, char* code, int code_i, int code_len) {
    if (TEST_PARSE_TREE_FIND) {
        for (int i = 0; i < code_i; i++) {
            printf(" ");
        }
        
        printf(
            "Question: %c==%c Ask %s branch %s code_i:%d code_len:%d id:%d\n", 
            q->c, code[code_i], 
            (question_ask(q, code[code_i]) ? "True" : "False"), 
            (   
                question_ask(q, code[code_i]) ? 
                (q->question_true == NULL ? "NULL" : "False") : 
                (q->question_false == NULL ? "NULL" : "False")
            ),
            code_i,
            code_len,
            q->answer_id
        );
    }
    if (
        question_ask(q, code[code_i])
    ) {
        // True
        if (code_i + 2 >= code_len) return q->answer_id;
        if (q->question_true == NULL) return -1;
        return me_parse_tree_find_recurse(q->question_true, code, code_i + 1, code_len);
    } else {
        // if (code_i >= code_len) return -1;
        if (q->question_false == NULL) return -1;
        return me_parse_tree_find_recurse(q->question_false, code, code_i, code_len);
    }
}

parse_tree_t* me_parse_tree_create() {
    parse_tree_t* mept = malloc(sizeof(parse_tree_t));
    mept->next_id = 0;
    mept->first_question = NULL;

    return mept;
}   

parse_tree_t* me_parse_tree_create_from_blueprint_set(
    math_structure_blueprint_set_t* msbs
) {
    parse_tree_t* pt = me_parse_tree_create();
    
    if (ME_PARSE_TREE_CREATE_FROM_BLUEPRINT_SET)
    printf("Testing parse tree create from blueprint set\n");
    
    for (int i = 0; i < msbs->msb_i; i++) {
        if (ME_PARSE_TREE_CREATE_FROM_BLUEPRINT_SET)
        printf("entering code %d: %s \n", i, msbs->msb_arr[i].code);
        me_parse_tree_append(pt, msbs->msb_arr[i].code, i, msbs->msb_arr[i].special);
    }

    return pt;
}


/**
 * start with the unknown then go to what is known then add questions until 
 * good.
 * 
 *  - [ ] Only Increment if it is a new character that is true. 
 *  - [ ] fix the id
 */
void me_parse_tree_append(
    parse_tree_t* mept, 
    char* code, 
    int id, 
    enum special_structure special
) {
    // Find location
    struct question* cur;
    int code_i = 0;
    int code_len = strlen(code);
    int flag_null_question_result = TRUE;

    // First Quesiton
    if (mept->first_question == NULL) {
        int new_id = (code_len == 1 ? id : -1);
        mept->first_question = question_create(special, new_id, code[0]);
        mept->total_questions = 1;

        if (TEST_PARSE_TREE_APPEND)
        printf("Created New Question c:\'%c\' id:%d\n", code[code_i], new_id);
        
        if (code_len == 1) return;
    }
    
    // if the a question is NULL
    if (mept->first_question != NULL) {
        cur = mept->first_question;
        /* for (; */ 
        while (
            code_i < code_len && flag_null_question_result/* ; */
            // code_i++
        ) {
            
            // Branch True or False
            int answer = question_ask(cur, code[code_i]); 
            if (answer == TRUE  && cur->question_true != NULL) {
                if (TEST_PARSE_TREE_APPEND) {
                    for (int i = 0; i < code_i; i++) printf("\t");                
                    printf("TRUE '%c'=='%c' %d\n", code[code_i], cur->c, code_i);
                }
                cur = cur->question_true;
            } else if (answer == FALSE && cur->question_false != NULL) {
                if (TEST_PARSE_TREE_APPEND) {
                    for (int i = 0; i < code_i; i++) printf("  ");                
                    printf("FALSE '%c' != '%c' \n", code[code_i], cur->c, code_i);
                }
                cur = cur->question_false;
                
            } else if (cur->question_false == NULL && answer == FALSE) {
                // Creates the false branch
                int new_id = (code_i + 1 == code_len);
                cur->question_false = question_create(
                    SINGLE_CHARACTER, 
                    new_id,
                    code[code_i]
                );
                code_i++;
                cur = cur->question_false;
                
                if (TEST_PARSE_TREE_APPEND) {
                    for (int i = 0; i < code_i; i++) printf("  ");                
                    printf("FALSE NEW '%c' != '%c' \n", code[code_i], cur->c, code_i);
                }
                flag_null_question_result = FALSE;
                
            } else  {
                if (TEST_PARSE_TREE_APPEND) {
                    for (int i = 0; i < code_i; i++) printf("  ");                
                    printf("TRUE NEW '%c' == '%c' \n", code[code_i], cur->c, code_i);
                }
                flag_null_question_result = FALSE;
                // Permature end as in setting an id to a code that shorter then 
                // usual
            }
            
            if (answer == TRUE) code_i++;
        }
        
        // location to be set
        if (code_i + 1 == code_len && flag_null_question_result) {
            cur->answer_id = id;
            return;
        }
        
    }
    
    // We are up to a question that is NULL
    // Adds questions and sets them to the next true
    if (!flag_null_question_result) {
        
        // Loop through the 
        for (
            ; 
            code_i < code_len; 
            code_i++
        ) {
            int new_id = (code_i == code_len - 1 ? id : -1);
            // Create True
            question_t* next_question = question_create(
                special, 
                new_id, 
                code[code_i]);
            mept->total_questions++;
            cur->question_true = next_question;
            cur = next_question;
            if (TEST_PARSE_TREE_APPEND) {
                for (int i = 0; i < code_i; i++) printf("  ");                
                printf("Created New Question c:\'%c\' id:%d\n", code[code_i], new_id);
            }
        }
        
        // Found the location 
        // if () {

        // }
    }
}

void me_parse_tree_print(parse_tree_t* pt) {
    printf("\n\n...\n\nPrinting tree with %d questions\n", pt->total_questions);
    if (pt->first_question != NULL) me_parse_tree_print_question(pt->first_question, 0,-1);
}
void me_parse_tree_print_question(question_t* q, int d, int answer) {
    for (int i = 0; i < d; i++) printf("  ");
    printf("%s %d:\'%c\' true or false and %d id\n", (answer == TRUE ? "TRUE " : answer == FALSE ? "FALSE" : "FIRST"), d, q->c, q->answer_id);

    if (q->question_true != NULL) me_parse_tree_print_question(q->question_true, d+1, TRUE);
    if (q->question_false != NULL) me_parse_tree_print_question(q->question_false, d, FALSE);
}

void me_parse_tree_free(parse_tree_t* pt) {      
    question_free(pt->first_question);
    free(pt);
}





////////////////////////////////////////////////////////////////////////////////

int question_ask(question_t* cur, char c) {
    switch (cur->type) {
    case SINGLE_CHARACTER:
        return c == cur->c;
    case ALPHABETIC:
        return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
    case ALPHANUMERIC:
        return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9');
    default:
        return 0;
    }
}

question_t* question_create(enum special_structure type, int id, char c) {
    if (TEST_QUESTION_CREATE)
    printf("Creating Question %2d of '%c'\n", id, c);
    question_t* q = malloc(sizeof(question_t));
    q->type = type;
    q->answer_id = id;
    q->c = c;
    q->question_false = NULL;
    q->question_true = NULL;

    return q;
}

void question_free(question_t* q) {
    if (q->question_false != NULL) question_free(q->question_false);
    if (q->question_true != NULL) question_free(q->question_true);
    free(q);
}


/**
 *  Parse Tree Find Next Item
 */
void pt_find_next_item(
    char* buf,      int buf_size, 
    char* nword,    int* nword_size, 
    int* target_i 
) {

}