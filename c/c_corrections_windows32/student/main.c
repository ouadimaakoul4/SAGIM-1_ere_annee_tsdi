#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>

// Structure to hold student information
typedef struct {
    TCHAR name[100];
    TCHAR email[100];
    TCHAR address[100];
} Student;

// Global variables
HWND hNameEdit, hEmailEdit, hAddressEdit, hDisplayEdit;
Student* students = NULL; // Dynamic array to store students
int studentCount = 0;     // Number of students
int studentCapacity = 0;  // Capacity of the dynamic array

// Function prototypes
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CreateControls(HWND);
void AddStudent(const TCHAR* name, const TCHAR* email, const TCHAR* address);
void DisplayStudents(HWND hwnd);

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
    wc.lpszClassName = _T("StudentAppClass");
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, _T("Window Registration Failed!"), _T("Error!"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Creating the Window
    hwnd = CreateWindowEx(
        0,
        _T("StudentAppClass"),
        _T("Student Information App"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
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
            if (LOWORD(wParam) == 1) { // "Add" button
                TCHAR name[100], email[100], address[100];
                GetWindowText(hNameEdit, name, 100);
                GetWindowText(hEmailEdit, email, 100);
                GetWindowText(hAddressEdit, address, 100);

                // Add the student to the list
                AddStudent(name, email, address);

                // Clear the input fields
                SetWindowText(hNameEdit, _T(""));
                SetWindowText(hEmailEdit, _T(""));
                SetWindowText(hAddressEdit, _T(""));

                // Display all students
                DisplayStudents(hwnd);
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            // Free the dynamically allocated memory
            if (students) {
                free(students);
            }
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
    CreateWindow(_T("STATIC"), _T("Name:"), WS_VISIBLE | WS_CHILD, 10, 10, 100, 20, hwnd, NULL, NULL, NULL);
    hNameEdit = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL, 120, 10, 350, 20, hwnd, NULL, NULL, NULL);

    CreateWindow(_T("STATIC"), _T("Email:"), WS_VISIBLE | WS_CHILD, 10, 40, 100, 20, hwnd, NULL, NULL, NULL);
    hEmailEdit = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL, 120, 40, 350, 20, hwnd, NULL, NULL, NULL);

    CreateWindow(_T("STATIC"), _T("Address:"), WS_VISIBLE | WS_CHILD, 10, 70, 100, 20, hwnd, NULL, NULL, NULL);
    hAddressEdit = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL, 120, 70, 350, 20, hwnd, NULL, NULL, NULL);

    // Create "Add" button
    CreateWindow(_T("BUTTON"), _T("Add"), WS_VISIBLE | WS_CHILD, 10, 100, 100, 30, hwnd, (HMENU)1, NULL, NULL);

    // Create display area
    hDisplayEdit = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""), WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY, 10, 140, 460, 200, hwnd, NULL, NULL, NULL);
}

// Function to add a student
void AddStudent(const TCHAR* name, const TCHAR* email, const TCHAR* address) {
    // Resize the array if necessary
    if (studentCount >= studentCapacity) {
        studentCapacity = studentCapacity == 0 ? 1 : studentCapacity * 2;
        students = (Student*)realloc(students, studentCapacity * sizeof(Student));
        if (!students) {
            MessageBox(NULL, _T("Memory allocation failed!"), _T("Error!"), MB_ICONERROR | MB_OK);
            exit(1);
        }
    }

    // Add the student to the array
    _tcscpy(students[studentCount].name, name);
    _tcscpy(students[studentCount].email, email);
    _tcscpy(students[studentCount].address, address);
    studentCount++;
}

// Function to display all students
void DisplayStudents(HWND hwnd) {
    TCHAR displayText[1000] = _T("");
    int i;
    for (i = 0; i < studentCount; i++) {
        TCHAR studentInfo[300];
        _stprintf(studentInfo, _T("\nName: %s\nEmail: %s\nAddress: %s\n\n"), students[i].name, students[i].email, students[i].address);
        _tcscat(displayText, studentInfo);
    }
    SetWindowText(hDisplayEdit, displayText);
}
