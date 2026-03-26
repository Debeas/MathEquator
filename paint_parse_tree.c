#include "paint_parse_tree.h"
#include <windows.h>


#define PPT_RADIUS 10 

#define PPT_TOTAL_MARGIN 20
#define PPT_BRANCH_LENGTH 50

#define TEST_PAINT_BOX_RECTANGLE 1 
#define TEST_PAINT_PARSE_TREE_QUESTION_BRANCHES 1 
#define TEST_PAINT_PARSE_TREE 1 

/**
 * Need to be able to paint, rounded rectangle for nodes, rectangle text for 
 * Start and Id: Name, Lines to connect them 
 * 
 * need something that is either recursive or List to stack options will use the
 * questions but they don't go backwards so I need a question stack 
 * 
 * Alg:
 *  - Place Rect Start at say start_x start_y with Margin say 20
 *  - then create alg that goes to each question with a line starting horizontal
 * the BRANCH_LENGTH then down then into it then draws it then returns the 
 * aquired height then go to the next one.
 *  - At the end Draw Rect End with Id and value
 *  - then continue each branch that is true. 
 * 
 * Recursion
 *  - Call the true then it should do the true line then call its next true line
 *  - After the the true then it should handle the false using the height ptr 
 * hold to slowly drop it down. 
 * 
 * Paint Parse Tree
 *  - Draw line
 *  - Draw box 
 *  - Set Recurse
 * 
 * Recursion Problem
 *  - need to set line start position and line end position inorder to not
 * double recurse over the same thing. and then only do a single false recursion '
 * 
 * It starts the start then the first question, but the false needs then same 
 * line as the first question start 
 * 
 * Alternatively we have each branch print its on question squircle then its 
 * lengths. Issue is calculating depth which is dodgy
 * 
 */
void paint_parse_tree(HDC hdc, parse_tree_t* pt, int box_x, int box_y) {
    int cur_x = box_x + PPT_TOTAL_MARGIN;
    int cur_y = box_y + PPT_TOTAL_MARGIN;

    int start_x = box_x;
    int start_y = box_y;

    int width_hold = 0;
    int height_hold = 0;

    // Char
    char c[2]; 
    c[0] = pt->first_question->c;
    c[1] = '\0';
    
    // Start Box
    int start_box_width = 0;
    int start_box_height = 0;
    if (TEST_PAINT_PARSE_TREE) {
        printf("Placing Start at (%d, %d)\n", box_x, box_y);
    }
    paint_box_rectangle(hdc, box_x, box_y, "Start", &start_box_width, &start_box_height);
    start_x = box_x + start_box_width;
    start_y = box_y;
    
    // First Question is a straight line
    int cur_height = 0;
    int first_q_x = start_x + PPT_BRANCH_LENGTH;
    int first_q_y = start_y;
    if (TEST_PAINT_PARSE_TREE) {
        printf("Placing \'%c\' at (%d, %d)\n", pt->first_question->c, box_x, box_y);
    }

    // Firse Quesiton
    paint_line_to_2(hdc, start_x, start_y + PPT_RADIUS, first_q_x, first_q_y + PPT_RADIUS, TRUE);
    paint_curved_rectangle(hdc, first_q_x, first_q_y, c, &width_hold, &height_hold);
    paint_parse_tree_question_branches(hdc, pt->first_question, start_x, start_y + PPT_RADIUS, start_x, start_y + PPT_RADIUS, first_q_x+width_hold, first_q_y, width_hold, &cur_height);
}


/**
 * The start_x and start_y are the top of the back of the question box 
 * already drawn
 * 
 * The line_start_x and line_start_y are the previous back of the thing inorder 
 * to have the go well.
 * 
 * Should update the thing
 * 
 * Paints the line to the true then box of true. 
 * 
 * Essentially the question box is already drawn we need to draw its respective
 * children. while passing along its thing
 * 
 */ 
void paint_parse_tree_question_branches(
    HDC hdc, question_t* q, 
    int true_line_start_x, int true_line_start_y,
    int false_line_start_x, int false_line_start_y,
    int x_start, int y_start, 
    int width,
    int* ptr_height
) {
    if (q == NULL) {
        printf("SCREAM NULL QUESTION PAINTED\n");
        exit(1);
    }

    int height = *ptr_height;
    int width_hold = 0;
    int height_hold = 0;
    
    // 3 Possible childs
    int x_finish = x_start + PPT_BRANCH_LENGTH;
    int y_finish = y_start;
    int x_true = x_start + PPT_BRANCH_LENGTH;
    int y_true = y_start;
    int x_false = x_start - width_hold;
    int y_false = y_start;
    
    // Irrelevant
    char c[2];
    c[0] = q->c;
    c[1] = '\0';
    *ptr_height = 0;
    
    // Finish
    if (q->answer_id != -1) {
        if (TEST_PAINT_PARSE_TREE_QUESTION_BRANCHES) {
            printf("Placing finish %c at %d %d\n", q->c, x_finish, y_finish);
        }
        paint_line_to_2(hdc, true_line_start_x, y_finish + PPT_RADIUS, x_finish, y_finish + PPT_RADIUS, TRUE);
        paint_box_rectangle(hdc, x_finish, y_finish, c, &width_hold, &height_hold);
        y_true += height_hold;
        y_false += height_hold;
        *ptr_height += height_hold;
    }
    
    // True
    if (q->question_true != NULL) {
        if (TEST_PAINT_PARSE_TREE_QUESTION_BRANCHES) {
            printf("Placing true %c at %d %d\n", q->c, x_true, y_true);
        }
        c[0] = q->question_true->c;
        paint_line_to_2(hdc, x_start, y_start + PPT_RADIUS, x_true, y_true + PPT_RADIUS, TRUE);
        paint_curved_rectangle(hdc, x_true, y_true, c, &width_hold, &height_hold);
        paint_parse_tree_question_branches(hdc, q->question_true, x_true + width_hold, y_true, x_true + width_hold, y_true, x_true + width_hold, y_true, width_hold, &height_hold);
        y_false += height_hold;
        *ptr_height += height_hold;
    }
    
    // False Branch
    if (q->question_false != NULL) {
        if (TEST_PAINT_PARSE_TREE_QUESTION_BRANCHES) {
            printf("Placing false %c at %d %d\n", q->c, x_false, y_false);
        }
        c[0] = q->question_false->c;
        paint_line_to_2(hdc, false_line_start_x, false_line_start_y, x_false, y_false + PPT_RADIUS, TRUE);
        paint_curved_rectangle(hdc, x_false, y_false, c, &width_hold, &height_hold);
        paint_parse_tree_question_branches(hdc, q->question_false, x_false + width_hold, y_false, false_line_start_x, false_line_start_y, x_false, y_false + PPT_RADIUS, width_hold, &height_hold);
        *ptr_height += height_hold;
    }
    
}

/**
 * 
 * Essentially line travels horizontally or verticall then does a radius turn 
 * that is 90 degrees then continues, the orientation has a true or false value
 * being whether todo the horizontal part first.  
 * 
 */
void paint_line_to(HDC hdc, int x1, int y1, int x2, int y2, int orientation) {
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(0,0,0)); 
    HPEN oldPen = SelectObject(hdc, pen);

    int dx = x2 - x1;
    int dy = y2 - y1;
    int xa;    
    int ya;    
    int xb;    
    int yb;    

    // Line to
    if (orientation) {
        // Horizontal Line
        if (dx > 0. || dx < 0.) {
            xa = x1 + dx + (dx > 0 ? - PPT_RADIUS : PPT_RADIUS);
            ya = y1;
            MoveToEx(hdc, x1, y1, NULL);
            LineTo(hdc, xa, ya);
        }
        
        // Vertical Line
        if (dy > 0. || dy < 0.) {
            xb = x2;
            yb = y2 - dy + (dy < 0 ? - PPT_RADIUS : PPT_RADIUS);
            MoveToEx(hdc, xb, yb, NULL);
            LineTo(hdc, xb, yb);
        }

        // Arc
        if ((dy > 0. || dy < 0.) && (dx > 0. || dx < 0.)) {
            int left  = xa < xb ? xa : xb;
            int right = xa < xb ? xb : xa;
            int top   = ya > yb ? ya : yb;
            int bottom= ya > yb ? yb : ya;
            Arc(hdc, left, top, right, bottom, xa, ya, xb, yb);
        }
    } else {
        // Vertical Line
        if (dy > 0. || dy < 0.) {
            xa = x1;
            ya = y1 + dy + (dy > 0 ? - PPT_RADIUS : PPT_RADIUS);
            MoveToEx(hdc, x1, y1, NULL);
            LineTo(hdc, xa, ya);
        }
        
        // Horizontal Line
        if (dx > 0. || dx < 0.) {
            xb = x2 - dx + (dx < 0 ? - PPT_RADIUS : PPT_RADIUS);;
            yb = y2;
            MoveToEx(hdc, xb, yb, NULL);
            LineTo(hdc, xb, yb);
        }

        // Arc
        if ((dy > 0. || dy < 0.) && (dx > 0. || dx < 0.)) {
            int left  = xa < xb ? xa : xb;
            int right = xa < xb ? xb : xa;
            int top   = ya > yb ? ya : yb;
            int bottom= ya > yb ? yb : ya;
            Arc(hdc, left, top, right, bottom, xa, ya, xb, yb);
        }
    }

    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}

/**
 * Option two 
 *  - have the line do half the of the dx - radius then drop the dy do the 
 * rest of the dx
 */
void paint_line_to_2(HDC hdc, int x1, int y1, int x2, int y2, int orientation) {
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(0,0,0)); 
    HPEN oldPen = SelectObject(hdc, pen);

    int dx = x2 - x1;
    int dy = y2 - y1;

    if (dy < 2 * PPT_RADIUS) {
        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
    } else {
        // First
        int xa1 = x1;
        int ya1 = y1;
        int xa2 = x1 + (dx / 2) + (dx > 0 ? - PPT_RADIUS : PPT_RADIUS);
        MoveToEx(hdc, xa1, ya1, NULL);
        LineTo(hdc, xa2, ya1);
        
        // Drop
        int xb1 = x1 + (dx / 2); 
        int yb1 = y1 + (dy > 0 ? PPT_RADIUS : - PPT_RADIUS); 
        int xb2 = xb1;
        int yb2 = y1 + dy + (dy > 0 ? - PPT_RADIUS : PPT_RADIUS);
        MoveToEx(hdc, xb1, yb1, NULL);
        LineTo(hdc, xb2, yb2);

        // Second
        int xc1 = x1 + dx / 2 + (dx > 0 ? PPT_RADIUS : - PPT_RADIUS);
        int yc1 = y2;
        int xc2 = x2;
        int yc2 = y2;
        MoveToEx(hdc, xc1, yc1, NULL);
        LineTo(hdc, xc2, yc2);

        // First Arc 
        int xl1 = xa2 - PPT_RADIUS;
        int xr1 = xb1;
        Arc(
            hdc, 
            xl1, y1,                  // Left     top
            xr1, y1+2*PPT_RADIUS,     // Right    bottom
            xb1, yb1,//, // End 
            xa2, ya1 // start
            // TRUE
        );
        
        // Second Arc 
        int xl2 = xb2;
        int xr2 = xb2 + 2 * PPT_RADIUS;
        Arc(
            hdc, 
            xl2, yb2 - PPT_RADIUS,  // Left     top
            xr2, yc1,               // Right    bottom
            xb2, yb2,                 // start
            xc1, yc1//,               // End 
            // TRUE
        );
    }

    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}


/**
 * Round cornered Rectangle with text inside,
 */
void paint_curved_rectangle(HDC hdc, int x, int y, char* text, int* ptr_width, int* ptr_height) {
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(0,0,0)); 
    HPEN oldPen = SelectObject(hdc, pen);
 
    int width;
    int height;
    paint_text_store_dimesions(hdc, x + PPT_RADIUS, y + PPT_RADIUS, text, &width, &height);

    // X coordinates
    int right_m1 = x + width + PPT_RADIUS;
    int right = x + width + PPT_RADIUS * 2;
    int left_p1 = x + PPT_RADIUS;
    int left = x;
    
    // Y coordinates
    int top_m1      = y + PPT_RADIUS;
    int top         = y;
    int bottom_p1   = y + height + PPT_RADIUS;
    int bottom      = y + height + PPT_RADIUS * 2;

    // Top Horizontal Line 
    MoveToEx(hdc, left_p1, top, NULL);
    LineTo(hdc, right_m1, top);
    
    // Bottom Horizontal Line 
    MoveToEx(hdc, left_p1, bottom, NULL);
    LineTo(hdc, right_m1, bottom);

    // Left Vertical Line
    MoveToEx(hdc, left, top_m1, NULL);
    LineTo(hdc, left, bottom_p1);

    // Right Vertical Line
    MoveToEx(hdc,   right, top_m1, NULL);
    LineTo(hdc,     right, bottom_p1);

    // Top Left Arc
    Arc(hdc, left, top, left_p1 + PPT_RADIUS, top_m1 + PPT_RADIUS, left_p1, top, left, top_m1);
    
    // Top Right Arc
    Arc(hdc, right_m1 - PPT_RADIUS, top, right, top_m1 + PPT_RADIUS, right, top_m1, right_m1, top);

    // Bottom Left Arc
    Arc(hdc, left, bottom_p1 - PPT_RADIUS, left_p1 + PPT_RADIUS, bottom, left, bottom_p1, left_p1, bottom);
    
    // Bottom Right Arc
    Arc(hdc, right_m1 - PPT_RADIUS, bottom_p1 - PPT_RADIUS, right, bottom, right_m1, bottom, right, bottom_p1);

    SelectObject(hdc, oldPen);
    DeleteObject(pen);

    *ptr_width = width + 2 * PPT_RADIUS;
    *ptr_height = height + 2 * PPT_RADIUS;
}

void paint_text_store_dimesions(HDC hdc, int x, int y, char* text, int* ptr_width, int* ptr_height) {
    HFONT font = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial" );
    HFONT hOldFont = (HFONT)SelectObject(hdc, font);

    // int height = 0;
    // int width = 0;
    // // Height
    // TEXTMETRIC tm = {0};
    // GetTextMetrics(hdc, &tm);
    // height = tm.tmHeight + tm.tmExternalLeading;
    // // Width
    // for (int text_i = 0; text[text_i] != '\0'; text_i++) {
    //     int sub = 0;
    //     GetCharWidth32(hdc, text[text_i], text[text_i], &sub);
    //     width += sub;
    // }

    // Another way to get width/height
    SIZE size;
    GetTextExtentPoint32(hdc, text, strlen(text), &size);
    *ptr_width = size.cx;
    *ptr_height = size.cy;

    TextOut(hdc, x,y, text, strlen(text));
    
    SelectObject(hdc, hOldFont);
    DeleteObject(font);
}

/**
 * sharp cornered Rectangle with text inside,
 */
void paint_box_rectangle(HDC hdc, int x, int y, char* text, int* ptr_width, int* ptr_height) {
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(0,0,0)); 
    HPEN oldPen = SelectObject(hdc, pen);

    int width;
    int height;
    paint_text_store_dimesions(hdc, x + PPT_RADIUS, y + PPT_RADIUS, text, &width, &height);

    int left = x, 
        right = x + width + 2 * PPT_RADIUS, 
        top = y, 
        bottom = y + height + 2 * PPT_RADIUS;

    // Top Horizontal Line 
    MoveToEx(hdc, left, top, NULL);
    LineTo(hdc, right, top);
    
    // Bottom Horizontal Line 
    MoveToEx(hdc, left, bottom, NULL);
    LineTo(hdc, right, bottom);

    // Left Vertical Line
    MoveToEx(hdc, left, top, NULL);
    LineTo(hdc, left, bottom);

    // Right Vertical Line
    MoveToEx(hdc,   right, top, NULL);
    LineTo(hdc,     right, bottom);

    SelectObject(hdc, oldPen);
    DeleteObject(pen);

    *ptr_width = width + 2 * PPT_RADIUS;
    *ptr_height = height + 3 * PPT_RADIUS;

    if (TEST_PAINT_BOX_RECTANGLE) {
        printf("\t (%d, %d)\n", x, y);
    }
}


