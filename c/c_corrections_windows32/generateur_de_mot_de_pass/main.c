#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constantes pour les ID des contrôles
#define ID_LENGTH_EDIT 1
#define ID_INCLUDE_NUMBERS 2
#define ID_INCLUDE_LETTERS 3
#define ID_INCLUDE_SPECIALS 4
#define ID_GENERATE_BUTTON 5
#define ID_PASSWORD_STATIC 6

// Déclaration des fonctions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void GeneratePassword(HWND hwnd);

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
    wc.lpszClassName = TEXT("PasswordGeneratorClass");
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, TEXT("Échec de l'enregistrement de la classe de fenêtre !"), TEXT("Erreur !"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Création de la fenêtre
    hwnd = CreateWindowEx(0, TEXT("PasswordGeneratorClass"), TEXT("Générateur de Mot de Passe"),
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, hInstance, NULL);

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
            CreateWindow(TEXT("STATIC"), TEXT("Longueur du mot de passe:"), WS_VISIBLE | WS_CHILD, 10, 10, 200, 20, hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 10, 50, 20, hwnd, (HMENU)ID_LENGTH_EDIT, NULL, NULL);

            CreateWindow(TEXT("BUTTON"), TEXT("Inclure des chiffres"), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 10, 40, 150, 20, hwnd, (HMENU)ID_INCLUDE_NUMBERS, NULL, NULL);
            CreateWindow(TEXT("BUTTON"), TEXT("Inclure des lettres"), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 10, 70, 150, 20, hwnd, (HMENU)ID_INCLUDE_LETTERS, NULL, NULL);
            CreateWindow(TEXT("BUTTON"), TEXT("Inclure des caractères spéciaux"), WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 10, 100, 200, 20, hwnd, (HMENU)ID_INCLUDE_SPECIALS, NULL, NULL);

            CreateWindow(TEXT("BUTTON"), TEXT("Générer Mot de Passe"), WS_VISIBLE | WS_CHILD, 10, 130, 150, 30, hwnd, (HMENU)ID_GENERATE_BUTTON, NULL, NULL);

            CreateWindow(TEXT("STATIC"), TEXT("Mot de Passe Généré:"), WS_VISIBLE | WS_CHILD, 10, 170, 150, 20, hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("STATIC"), TEXT(""), WS_VISIBLE | WS_CHILD, 160, 170, 200, 20, hwnd, (HMENU)ID_PASSWORD_STATIC, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == ID_GENERATE_BUTTON) {
                GeneratePassword(hwnd);
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

// Fonction pour générer un mot de passe
void GeneratePassword(HWND hwnd) {
    TCHAR lengthStr[10];
    GetWindowText(GetDlgItem(hwnd, ID_LENGTH_EDIT), lengthStr, 10);
    int length = _ttoi(lengthStr);

    if (length <= 0) {
        MessageBox(hwnd, TEXT("Veuillez entrer une longueur valide !"), TEXT("Erreur"), MB_ICONERROR | MB_OK);
        return;
    }

    // Vérifier les options sélectionnées
    BOOL includeNumbers = SendDlgItemMessage(hwnd, ID_INCLUDE_NUMBERS, BM_GETCHECK, 0, 0) == BST_CHECKED;
    BOOL includeLetters = SendDlgItemMessage(hwnd, ID_INCLUDE_LETTERS, BM_GETCHECK, 0, 0) == BST_CHECKED;
    BOOL includeSpecials = SendDlgItemMessage(hwnd, ID_INCLUDE_SPECIALS, BM_GETCHECK, 0, 0) == BST_CHECKED;

    if (!includeNumbers && !includeLetters && !includeSpecials) {
        MessageBox(hwnd, TEXT("Veuillez sélectionner au moins un type de caractère !"), TEXT("Erreur"), MB_ICONERROR | MB_OK);
        return;
    }

    // Définir les caractères possibles
    TCHAR numbers[] = TEXT("0123456789");
    TCHAR letters[] = TEXT("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    TCHAR specials[] = TEXT("!@#$%^&*()_+-=[]{}|;:,.<>?");

    TCHAR allChars[200] = TEXT("");
    if (includeNumbers) _tcscat(allChars, numbers);
    if (includeLetters) _tcscat(allChars, letters);
    if (includeSpecials) _tcscat(allChars, specials);

    int allCharsLength = _tcslen(allChars);

    // Générer le mot de passe
    TCHAR password[100] = TEXT("");
    srand((unsigned int)time(NULL)); // Initialiser le générateur de nombres aléatoires
    int i;
    for (i = 0; i < length; i++) {
        int index = rand() % allCharsLength;
        password[i] = allChars[index];
    }
    password[length] = TEXT('\0');

    // Afficher le mot de passe
    SetWindowText(GetDlgItem(hwnd, ID_PASSWORD_STATIC), password);
}
