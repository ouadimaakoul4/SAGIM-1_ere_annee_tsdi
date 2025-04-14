#include <windows.h>
#include <tchar.h>
#include <stdio.h>

// Constantes pour les ID des contrôles
#define ID_NAME_EDIT 1
#define ID_NOTE_EDIT 2
#define ID_ADD_BUTTON 3
#define ID_CALCULATE_BUTTON 4
#define ID_THRESHOLD_EDIT 5
#define ID_RESULT_STATIC 6
#define ID_LISTBOX 7

// Structure pour stocker les étudiants
typedef struct {
    TCHAR name[100];
    double note;
} Student;

// Variables globales
Student students[100];
int studentCount = 0;

// Déclaration des fonctions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void AddStudent(HWND hwnd);
void CalculateStatistics(HWND hwnd);

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
    wc.lpszClassName = TEXT("GradeManagerClass");
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, TEXT("Échec de l'enregistrement de la classe de fenêtre !"), TEXT("Erreur !"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Création de la fenêtre
    hwnd = CreateWindowEx(0, TEXT("GradeManagerClass"), TEXT("Système de Gestion de Notes"),
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 400, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, TEXT("Échec de la création de la fenêtre !"), TEXT("Erreur !"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Boucle de messages
    while (GetMessage(&Msg, NULL, 0, 0)) {
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
            CreateWindow(TEXT("STATIC"), TEXT("Nom de l'étudiant:"), WS_VISIBLE | WS_CHILD, 10, 10, 150, 20, hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 160, 10, 200, 20, hwnd, (HMENU)ID_NAME_EDIT, NULL, NULL);

            CreateWindow(TEXT("STATIC"), TEXT("Note:"), WS_VISIBLE | WS_CHILD, 10, 40, 150, 20, hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 160, 40, 200, 20, hwnd, (HMENU)ID_NOTE_EDIT, NULL, NULL);

            CreateWindow(TEXT("BUTTON"), TEXT("Ajouter Étudiant"), WS_VISIBLE | WS_CHILD, 10, 70, 150, 30, hwnd, (HMENU)ID_ADD_BUTTON, NULL, NULL);

            CreateWindow(TEXT("BUTTON"), TEXT("Calculer Statistiques"), WS_VISIBLE | WS_CHILD, 10, 110, 150, 30, hwnd, (HMENU)ID_CALCULATE_BUTTON, NULL, NULL);

            CreateWindow(TEXT("STATIC"), TEXT("Seuil de note:"), WS_VISIBLE | WS_CHILD, 10, 150, 150, 20, hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 160, 150, 200, 20, hwnd, (HMENU)ID_THRESHOLD_EDIT, NULL, NULL);

            CreateWindow(TEXT("STATIC"), TEXT("Résultats:"), WS_VISIBLE | WS_CHILD, 10, 190, 150, 20, hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("STATIC"), TEXT(""), WS_VISIBLE | WS_CHILD, 160, 190, 400, 20, hwnd, (HMENU)ID_RESULT_STATIC, NULL, NULL);

            CreateWindow(TEXT("LISTBOX"), NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL, 10, 220, 550, 150, hwnd, (HMENU)ID_LISTBOX, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case ID_ADD_BUTTON:
                    AddStudent(hwnd);
                    break;
                case ID_CALCULATE_BUTTON:
                    CalculateStatistics(hwnd);
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

// Fonction pour ajouter un étudiant
void AddStudent(HWND hwnd) {
    TCHAR name[100], noteStr[100];
    GetWindowText(GetDlgItem(hwnd, ID_NAME_EDIT), name, 100);
    GetWindowText(GetDlgItem(hwnd, ID_NOTE_EDIT), noteStr, 100);

    if (_tcslen(name) > 0 && _tcslen(noteStr) > 0) {
        double note = _tcstod(noteStr, NULL);
        _tcscpy(students[studentCount].name, name);
        students[studentCount].note = note;
        studentCount++;

        // Ajouter l'étudiant à la liste
        TCHAR studentInfo[200];
        _stprintf(studentInfo, TEXT("%s - %.2f"), name, note);
        SendDlgItemMessage(hwnd, ID_LISTBOX, LB_ADDSTRING, 0, (LPARAM)studentInfo);

        // Effacer les champs de saisie
        SetWindowText(GetDlgItem(hwnd, ID_NAME_EDIT), TEXT(""));
        SetWindowText(GetDlgItem(hwnd, ID_NOTE_EDIT), TEXT(""));
    }
}

// Fonction pour calculer les statistiques
void CalculateStatistics(HWND hwnd) {
	int i;
    if (studentCount == 0) {
        SetWindowText(GetDlgItem(hwnd, ID_RESULT_STATIC), TEXT("Aucun étudiant saisi !"));
        return;
    }

    double sum = 0, bestNote = students[0].note, worstNote = students[0].note;
    for (i = 0; i < studentCount; i++) {
        sum += students[i].note;
        if (students[i].note > bestNote) bestNote = students[i].note;
        if (students[i].note < worstNote) worstNote = students[i].note;
    }
    double average = sum / studentCount;

    // Afficher les statistiques
    TCHAR resultStr[500];
    _stprintf(resultStr, TEXT("Moyenne: %.2f | Meilleure note: %.2f | Pire note: %.2f"), average, bestNote, worstNote);
    SetWindowText(GetDlgItem(hwnd, ID_RESULT_STATIC), resultStr);

    // Lister les étudiants ayant une note supérieure au seuil
    TCHAR thresholdStr[100];
    GetWindowText(GetDlgItem(hwnd, ID_THRESHOLD_EDIT), thresholdStr, 100);
    double threshold = _tcstod(thresholdStr, NULL);

    SendDlgItemMessage(hwnd, ID_LISTBOX, LB_RESETCONTENT, 0, 0); // Effacer la liste
    
    for (i = 0; i < studentCount; i++) {
        if (students[i].note > threshold) {
            TCHAR studentInfo[200];
            _stprintf(studentInfo, TEXT("%s - %.2f"), students[i].name, students[i].note);
            SendDlgItemMessage(hwnd, ID_LISTBOX, LB_ADDSTRING, 0, (LPARAM)studentInfo);
        }
    }
}
