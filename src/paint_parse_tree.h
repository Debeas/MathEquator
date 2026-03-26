#ifndef PAINT_PARSE_TREE_H
#define PAINT_PARSE_TREE_H

#include "me_parse_tree.h"

#include <windows.h>

void paint_text_store_dimesions(HDC hdc, int x, int y, char* text, int* ptr_width, int* ptr_height);

void paint_line_to(HDC hdc, int x1, int y1, int x2, int y2, int orientation);

void paint_curved_rectangle(HDC hdc, int x, int y, char* text, int* ptr_width, int* ptr_height);
void paint_box_rectangle(HDC hdc, int x, int y, char* text, int* ptr_width, int* ptr_height);

// void paint_parse_tree_question_branches(HDC hdc, question_t* q, int start_x, int start_y, int* height);
void paint_parse_tree(HDC hdc, parse_tree_t* pt, int start_x, int start_y);
void paint_parse_tree_question_branches(
    HDC hdc, question_t* q, 
    int true_line_start_x, int true_line_start_y,
    int false_line_start_x, int false_line_start_y,
    int x_start, int y_start, 
    int width,    
    int* ptr_height
);

void paint_line_to_2(HDC hdc, int x1, int y1, int x2, int y2, int orientation);
#endif