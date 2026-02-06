#include <windows.h>
#include "me_paint.h"
#include "me_entry.h"

/**
 * Datatype to hold next request
 */

int not_bracket_parenthesis_brace_angles(char c);

void math_entry_handle(HWND hwndCtrl, struct math_entry_data* data, math_structure_blueprint_set_t* msbs) {
    int DATA_NULL = data == NULL;
    int buf_size = 100;
    char* buf = malloc(sizeof(char) * buf_size); 
    char* buf_2 = malloc(sizeof(char) * buf_size); 
    // Edit(hwndCtrl, buf, buf_size);
    GetWindowText(hwndCtrl, buf, buf_size);
    // // Create Sturcture
    // math_structure_t* msb_head = NULL;

    // Finding Code
    int target_i = -2;
    int nword_len = -1;
    int shift_i = 0;

    int cur_x;
    int cur_y;
    if (!DATA_NULL) {
        cur_x = data->start_x;
        cur_y = data->start_y;
    } else printf("Data is null\n");

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

        // 
        if (target_i == -1) {

        }

        printf("Found symbol %s in %d %s \n", buf_2, target_i, msbs->msb_arr[target_i].character);

        // Adding a found Structure;
        if (target_i >= 0 && !DATA_NULL) {
            math_entry_data_append(data, &(msbs->msb_arr[target_i]), cur_x, cur_y, NULL);
        }

        
        if (target_i != -1) target_i = -2;
        
        shift_i += nword_len;
    }
    printf("buf = \"%s\" buf2 = \"%s\" len=%d\n", buf, buf_2, nword_len);



    free(buf_2);
    free(buf);
}

void math_entry_create_math_structure() {

}

/**
 * This needs testing
 */
int me_extract_next_word(char* buf, int buf_size, char* nword, int nword_size) {
    
    // First Spaces
    int i = 0;
    while (i < buf_size && buf[i] == ' ') i++;

    // If bracket just added because of bracket thing.
    if (buf[i] == '(' || buf[i] == ')') {
        nword[0] = buf[i];
        nword[1] = '\0';
        return 1;
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
    return FALSE;

}

int not_bracket_parenthesis_brace_angles(char c) {
    return !(c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']');
}

 //|\   /|\   /|\   /|\   /|\   /|\   /|\   /|\   /|\   /|\   /|\   /|\   /|\   
 // \\ // \\ // \\ // \\ MATHEMATICS ENTRY // \\ // \\ // \\ // \\ // \\ // \\ /
//   \|/   \|/   \|/   \|/   \|/   \|/   \|/   \|/   \|/   \|/   \|/   \|/   \|/


math_entry_data_t* math_entry_data_create(int start_x, int start_y) {
    math_entry_data_t* med = malloc(sizeof(math_entry_data_t));
    med->i_request = 0;
    med->request_size = 0;
    med->start_x = start_x;
    med->start_y = start_y;
    med->requests = NULL;
    return med;
}

void math_entry_data_free(math_entry_data_t* med) {
    for (int i = 0; i < med->i_request; i++) {
        math_structure_free(med->requests[i]);
    }
    
    if (med->requests != NULL) free(med->requests);
    free(med);
}

void math_entry_data_append(
    math_entry_data_t* med, 
    math_structure_blueprint_t* msb, 
    int x, 
    int y, 
    math_structure_t** item_p_arr
) {
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

