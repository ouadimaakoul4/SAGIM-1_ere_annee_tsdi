#include <windows.h>
#include <tchar.h>
#include <stdio.h>

// Global variables
HWND hHtEdit, hTvaEdit, hTtcEdit;

// Function prototypes
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CreateControls(HWND);
void CalculateTtc(HWND hwnd);

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
    wc.lpszClassName = _T("TtcCalculatorClass");
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, _T("Window Registration Failed!"), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Creating the Window
    hwnd = CreateWindowEx(
        0,
        _T("TtcCalculatorClass"),
        _T("TTC Calculator"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
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
            if (LOWORD(wParam) == 1) { // "Calculate" button
                CalculateTtc(hwnd);
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
    // Create input fields
    CreateWindow(_T("STATIC"), _T("HT Price:"), WS_VISIBLE | WS_CHILD, 10, 10, 100, 20, hwnd, NULL, NULL, NULL);
    hHtEdit = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL, 120, 10, 200, 20, hwnd, NULL, NULL, NULL);

    CreateWindow(_T("STATIC"), _T("TVA Rate (%):"), WS_VISIBLE | WS_CHILD, 10, 40, 100, 20, hwnd, NULL, NULL, NULL);
    hTvaEdit = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL, 120, 40, 200, 20, hwnd, NULL, NULL, NULL);

    CreateWindow(_T("STATIC"), _T("TTC Price:"), WS_VISIBLE | WS_CHILD, 10, 70, 100, 20, hwnd, NULL, NULL, NULL);
    hTtcEdit = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | ES_READONLY, 120, 70, 200, 20, hwnd, NULL, NULL, NULL);

    // Create "Calculate" button
    CreateWindow(_T("BUTTON"), _T("Calculate"), WS_VISIBLE | WS_CHILD, 10, 100, 100, 30, hwnd, (HMENU)1, NULL, NULL);
}

// Function to calculate TTC
void CalculateTtc(HWND hwnd) {
    TCHAR htStr[100], tvaStr[100];
    double ht = 0, tva = 0, ttc = 0;

    // Get HT price
    GetWindowText(hHtEdit, htStr, 100);
    ht = _tcstod(htStr, NULL); // Convert TCHAR string to double

    // Get TVA rate
    GetWindowText(hTvaEdit, tvaStr, 100);
    tva = _tcstod(tvaStr, NULL); // Convert TCHAR string to double

    // Calculate TTC
    ttc = ht * (1 + tva / 100);

    // Display TTC
    TCHAR ttcStr[100];
    _stprintf(ttcStr, _T("%.2f"), ttc);
    SetWindowText(hTtcEdit, ttcStr);
}
