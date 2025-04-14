#include <windows.h>
#include <tchar.h>
#include <stdio.h>

// Constantes pour les ID des contrôles
#define ID_STUDENT_LIST 1
#define ID_TEACHER_LIST 2
#define ID_ADD_STUDENT 3
#define ID_ADD_TEACHER 4
#define ID_DELETE_STUDENT 5
#define ID_DELETE_TEACHER 6
#define ID_STUDENT_COUNT 7
#define ID_TEACHER_COUNT 8
#define ID_FIRST_NAME 9
#define ID_LAST_NAME 10

// Structure pour stocker les informations d'une personne
typedef struct {
    TCHAR firstName[100];
    TCHAR lastName[100];
} Person;

// Variables globales
Person students[100];
Person teachers[100];
int studentCount = 0;
int teacherCount = 0;

// Déclaration des fonctions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddPerson(Person* list, int* count, HWND hwnd, int listID, int countID);
void DeletePerson(Person* list, int* count, HWND hwnd, int listID, int countID);
void UpdateCount(HWND hwnd, int countID, int count);

// Fonction principale
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    // Initialisation de la classe de la fenêtre
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = TEXT("MyWindowClass");
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, TEXT("Échec de l'enregistrement de la classe de fenêtre !"), TEXT("Erreur !"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Création de la fenêtre
    hwnd = CreateWindowEx(0, TEXT("MyWindowClass"), TEXT("Gestion des Étudiants et Enseignants"),
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 400, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, TEXT("Échec de la création de la fenêtre !"), TEXT("Erreur !"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Boucle de messages
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

// Fonction de gestion des messages
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            // Création des contrôles
            CreateWindow(TEXT("STATIC"), TEXT("Prénom:"), WS_VISIBLE | WS_CHILD, 10, 10, 100, 20, hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 10, 200, 20, hwnd, (HMENU)ID_FIRST_NAME, NULL, NULL);

            CreateWindow(TEXT("STATIC"), TEXT("Nom:"), WS_VISIBLE | WS_CHILD, 10, 40, 100, 20, hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 40, 200, 20, hwnd, (HMENU)ID_LAST_NAME, NULL, NULL);

            CreateWindow(TEXT("STATIC"), TEXT("Étudiants:"), WS_VISIBLE | WS_CHILD, 10, 70, 100, 20, hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("LISTBOX"), NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL, 10, 90, 200, 150, hwnd, (HMENU)ID_STUDENT_LIST, NULL, NULL);

            CreateWindow(TEXT("STATIC"), TEXT("Enseignants:"), WS_VISIBLE | WS_CHILD, 220, 70, 100, 20, hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("LISTBOX"), NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL, 220, 90, 200, 150, hwnd, (HMENU)ID_TEACHER_LIST, NULL, NULL);

            CreateWindow(TEXT("BUTTON"), TEXT("Ajouter Étudiant"), WS_VISIBLE | WS_CHILD, 10, 250, 150, 30, hwnd, (HMENU)ID_ADD_STUDENT, NULL, NULL);
            CreateWindow(TEXT("BUTTON"), TEXT("Ajouter Enseignant"), WS_VISIBLE | WS_CHILD, 220, 250, 150, 30, hwnd, (HMENU)ID_ADD_TEACHER, NULL, NULL);

            CreateWindow(TEXT("BUTTON"), TEXT("Supprimer Étudiant"), WS_VISIBLE | WS_CHILD, 10, 290, 150, 30, hwnd, (HMENU)ID_DELETE_STUDENT, NULL, NULL);
            CreateWindow(TEXT("BUTTON"), TEXT("Supprimer Enseignant"), WS_VISIBLE | WS_CHILD, 220, 290, 150, 30, hwnd, (HMENU)ID_DELETE_TEACHER, NULL, NULL);

            CreateWindow(TEXT("STATIC"), TEXT("Nombre d'étudiants: 0"), WS_VISIBLE | WS_CHILD, 10, 330, 200, 20, hwnd, (HMENU)ID_STUDENT_COUNT, NULL, NULL);
            CreateWindow(TEXT("STATIC"), TEXT("Nombre d'enseignants: 0"), WS_VISIBLE | WS_CHILD, 220, 330, 200, 20, hwnd, (HMENU)ID_TEACHER_COUNT, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case ID_ADD_STUDENT:
                    AddPerson(students, &studentCount, hwnd, ID_STUDENT_LIST, ID_STUDENT_COUNT);
                    break;
                case ID_ADD_TEACHER:
                    AddPerson(teachers, &teacherCount, hwnd, ID_TEACHER_LIST, ID_TEACHER_COUNT);
                    break;
                case ID_DELETE_STUDENT:
                    DeletePerson(students, &studentCount, hwnd, ID_STUDENT_LIST, ID_STUDENT_COUNT);
                    break;
                case ID_DELETE_TEACHER:
                    DeletePerson(teachers, &teacherCount, hwnd, ID_TEACHER_LIST, ID_TEACHER_COUNT);
                    break;
            }
            break;
        }
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

// Fonction pour ajouter une personne
void AddPerson(Person* list, int* count, HWND hwnd, int listID, int countID) {
    TCHAR firstName[100], lastName[100];
    GetWindowText(GetDlgItem(hwnd, ID_FIRST_NAME), firstName, 100);
    GetWindowText(GetDlgItem(hwnd, ID_LAST_NAME), lastName, 100);

    if (_tcslen(firstName) > 0 && _tcslen(lastName) > 0) {
        _tcscpy(list[*count].firstName, firstName);
        _tcscpy(list[*count].lastName, lastName);
        (*count)++;

        TCHAR fullName[200];
        _stprintf(fullName, TEXT("%s %s"), firstName, lastName);
        SendDlgItemMessage(hwnd, listID, LB_ADDSTRING, 0, (LPARAM)fullName);

        UpdateCount(hwnd, countID, *count);

        // Effacer les champs de saisie
        SetWindowText(GetDlgItem(hwnd, ID_FIRST_NAME), TEXT(""));
        SetWindowText(GetDlgItem(hwnd, ID_LAST_NAME), TEXT(""));
    }
}

// Fonction pour supprimer une personne
void DeletePerson(Person* list, int* count, HWND hwnd, int listID, int countID) {
    int index = SendDlgItemMessage(hwnd, listID, LB_GETCURSEL, 0, 0);
    if (index != LB_ERR) {
        SendDlgItemMessage(hwnd, listID, LB_DELETESTRING, index, 0);
        int i;
        for (i = index; i < *count - 1; i++) {
            list[i] = list[i + 1];
        }
        (*count)--;
        UpdateCount(hwnd, countID, *count);
    }
}

// Fonction pour mettre à jour le compteur
void UpdateCount(HWND hwnd, int countID, int count) {
    TCHAR text[100];
    if (countID == ID_STUDENT_COUNT) {
        _stprintf(text, TEXT("Nombre d'étudiants: %d"), count);
    } else {
        _stprintf(text, TEXT("Nombre d'enseignants: %d"), count);
    }
    SetWindowText(GetDlgItem(hwnd, countID), text);
}
