#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Global variables
HWND hEdit;
HWND hButtons[16];
TCHAR buttonLabels[16][3] = {
    _T("7"), _T("8"), _T("9"), _T("/"),
    _T("4"), _T("5"), _T("6"), _T("*"),
    _T("1"), _T("2"), _T("3"), _T("-"),
    _T("0"), _T("."), _T("="), _T("+")
};

// Function prototypes
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CreateControls(HWND);
double EvaluateExpression(const TCHAR* expression);

// WinMain function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    // Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = _T("CalculatorClass");
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, _T("Window Registration Failed!"), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Creating the Window
    hwnd = CreateWindowEx(
        0,
        _T("CalculatorClass"),
        _T("Calculator"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 400,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL) {
        MessageBox(NULL, _T("Window Creation Failed!"), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_CREATE:
            CreateControls(hwnd);
            break;
        case WM_COMMAND:
            if((HWND)lParam == hButtons[14]) { // "=" button
                TCHAR buffer[256];
                GetWindowText(hEdit, buffer, 256);

                // Evaluate the expression
                double result = EvaluateExpression(buffer);

                // Display the result
                TCHAR resultStr[256];
                _stprintf(resultStr, _T("%.2f"), result); // Format the result to 2 decimal places
                SetWindowText(hEdit, resultStr);
            } else {
            	int i;
                for(i = 0; i < 16; i++) {
                    if((HWND)lParam == hButtons[i]) {
                        TCHAR buffer[256];
                        GetWindowText(hEdit, buffer, 256);
                        _tcscat(buffer, buttonLabels[i]);
                        SetWindowText(hEdit, buffer);
                        break;
                    }
                }
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Function to create controls
void CreateControls(HWND hwnd) {
    hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), 
        WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 
        10, 10, 260, 30, hwnd, NULL, NULL, NULL);

    int x = 10, y = 50;
    int i;
    for( i = 0; i < 16; i++) {
        hButtons[i] = CreateWindow(_T("BUTTON"), buttonLabels[i], 
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
            x, y, 60, 40, hwnd, NULL, NULL, NULL);
        x += 70;
        if((i + 1) % 4 == 0) {
            x = 10;
            y += 50;
        }
    }
}

// Function to evaluate the expression
double EvaluateExpression(const TCHAR* expression) {
    double num1 = 0, num2 = 0;
    TCHAR op = 0;
    int i = 0;

    // Parse the first number
    while (expression[i] && (isdigit(expression[i]) || expression[i] == '.')) {
        i++;
    }
    _stscanf(expression, _T("%lf"), &num1);

    // Parse the operator
    op = expression[i++];

    // Parse the second number
    _stscanf(expression + i, _T("%lf"), &num2);

    // Perform the calculation
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num1 / num2;
        default: return 0; // Invalid operator
    }
}
