/**
 * Equation Display Example
 - I need to make a 
 - 
 -  U+0283 is the unicode for the thing.
 */
#include <windows.h>
#include "basic_stuff.h"
#include "me_paint.h"
#include "me_entry.h"

#define EDIT_MATH 0x1001
#define BUTTON_MATH 0x1002
#define BUTTON_REPAINT 0x1003
#define BUTTON_BOX_PAINT 0x1004
 

LRESULT CALLBACK EditProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);
#define EQUATION_DISPLAY_EXAMPLE_CLASSNAME "EQUATION_DISPLAY_EXAMPLE_CLASSNAME"

static int main_box_paint = FALSE;

static HWND math_edit;
static math_structure_t* integral = {0};
static math_structure_blueprint_set_t* msbs_main = NULL;
static math_entry_data_t* med_main = NULL;

/**
 * Todo 
 *  - [x] Box Paint around everything
 *  - [ ] Handle '{' '}' to do nesting.
 *  - [ ] Work out a tree datatype to store stuff. 
 */
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Basic Stuff
    srand(time(NULL));
    make_console();
    msbs_main = math_structure_blueprint_set_defining();
    med_main = math_entry_data_create(100, 100);

    // Window
    HWND hwnd;
    WNDCLASSEX wc = {0};
    MSG Msg = {0};

    wc.lpfnWndProc = WindowProc;
    wc.lpszClassName = EQUATION_DISPLAY_EXAMPLE_CLASSNAME;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.cbSize = sizeof(WNDCLASSEX);
    RegisterClassEx(&wc);

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,                              // External Style
        EQUATION_DISPLAY_EXAMPLE_CLASSNAME,                                 // Class Name
        "Equation Display Example Window",                      // Window Name
        WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, // Window Style
        CW_USEDEFAULT,                                 // Initial X Position
        CW_USEDEFAULT,                                 // Initial Y Position
        1000,                                           // Initial Width
        800,                                           // Initial Height
        NULL,                                          //  Parent Handle
        NULL,      // Menu Handle No idea could be for chiled
        hInstance, // Handle to module associated
        NULL       // For the parameter struct ?
    );

    int x_start = 50;
    int y_start = 50;
    int edit_width = 800;
    int button_width = 50;
    int height = 20;
    int x_gap = 30;
    int y_gap = 20;

    // Buttons and things
    math_edit = CreateEdit(hInstance, hwnd, x_start, y_start, edit_width, height, "", EDIT_MATH, 0);
    CreateButton(hInstance, hwnd, x_start + x_gap + edit_width, y_start, button_width, height, "Enter", BUTTON_MATH);
    CreateButton(hInstance, hwnd, x_start + x_gap + edit_width, y_start + y_gap + height, button_width, height, "Re-Paint", BUTTON_REPAINT);
    CreateButton(hInstance, hwnd, x_start + x_gap + edit_width, y_start + 2*(y_gap + height), button_width, height, "Box-Paint", BUTTON_BOX_PAINT);
    // WNDPROC OldProc = (WNDPROC) SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR) EditProc);


    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}



LRESULT CALLBACK EditProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam) {
    switch (uMsg) {
        case WM_CLOSE: DestroyWindow(hwnd); return 0;
        case WM_DESTROY: PostQuitMessage(0); return 0;
        case WM_KEYDOWN: {
            switch (LOWORD(wParam)) {
                case VK_RETURN:
                math_entry_handle(math_edit, med_main, msbs_main);
                break;
            }
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lparam);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam) {
    switch (uMsg) {
        case WM_CLOSE: DestroyWindow(hwnd); return 0;
        case WM_DESTROY: PostQuitMessage(0); return 0;
        case WM_SIZE: {
            InvalidateRect(hwnd, NULL, TRUE); 
            break;
        }
        case WM_KEYDOWN: {
            switch (LOWORD(wParam)) {
                case VK_RETURN:
                printf("Enter\n");
                math_entry_handle(math_edit, med_main, msbs_main);
                break;
            }
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case BUTTON_MATH:
                    printf("\nMATH BUTTON\n");
                    math_entry_handle(math_edit, med_main, msbs_main);
                    break;
                case BUTTON_REPAINT:
                    printf("REPAINT BUTTON\n");
                    InvalidateRect(hwnd, NULL, TRUE); 
                    break;
                case BUTTON_BOX_PAINT: 
                    main_box_paint = !main_box_paint;
                    InvalidateRect(hwnd, NULL, TRUE);
                    break;
                default:
                    break;
            }
            break;
        }
        case WM_PAINT: {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd, &ps);

            math_data_paint(hdc, med_main, main_box_paint);

            EndPaint(hwnd, &ps);
        }
        default:
            break;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lparam);
}


////////////////////////////////////////////////////////////////////////////////
//  Functions that print in the symbols
/**
 * Boxes surrounding everything
 * They need to be draggable and shit
 * 
 * store things in data  
 */

