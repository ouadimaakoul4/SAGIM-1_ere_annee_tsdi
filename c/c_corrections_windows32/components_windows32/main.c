#include <windows.h>
#include <tchar.h>

// Constantes pour les ID des contrôles
#define ID_BUTTON_1 1
#define ID_BUTTON_2 2
#define ID_EDIT_1 3
#define ID_EDIT_2 4
#define ID_LABEL_1 5
#define ID_LABEL_2 6
#define ID_CHECKBOX 7
#define ID_RADIO_1 8
#define ID_RADIO_2 9
#define ID_LISTBOX 10

// Déclaration des fonctions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
    hwnd = CreateWindowEx(0, TEXT("MyWindowClass"), TEXT("Exemple de Fenêtre avec 10 Composants"),
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, NULL, NULL, hInstance, NULL);

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
            // Création des 10 composants
            // 1. Bouton 1
            CreateWindow(TEXT("BUTTON"), TEXT("Bouton 1"), WS_VISIBLE | WS_CHILD, 10, 10, 100, 30, hwnd, (HMENU)ID_BUTTON_1, NULL, NULL);

            // 2. Bouton 2
            CreateWindow(TEXT("BUTTON"), TEXT("Bouton 2"), WS_VISIBLE | WS_CHILD, 120, 10, 100, 30, hwnd, (HMENU)ID_BUTTON_2, NULL, NULL);

            // 3. Zone de texte 1
            CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 50, 200, 20, hwnd, (HMENU)ID_EDIT_1, NULL, NULL);

            // 4. Zone de texte 2
            CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 80, 200, 20, hwnd, (HMENU)ID_EDIT_2, NULL, NULL);

            // 5. Étiquette 1
            CreateWindow(TEXT("STATIC"), TEXT("Étiquette 1"), WS_VISIBLE | WS_CHILD, 10, 110, 100, 20, hwnd, (HMENU)ID_LABEL_1, NULL, NULL);

            // 6. Étiquette 2
            CreateWindow(TEXT("STATIC"), TEXT("Étiquette 2"), WS_VISIBLE | WS_CHILD, 120, 110, 100, 20, hwnd, (HMENU)ID_LABEL_2, NULL, NULL);

            // 7. Case à cocher
            CreateWindow(TEXT("BUTTON"), TEXT("Case à cocher"), WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 10, 140, 150, 20, hwnd, (HMENU)ID_CHECKBOX, NULL, NULL);

            // 8. Bouton radio 1
            CreateWindow(TEXT("BUTTON"), TEXT("Option 1"), WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON, 10, 170, 100, 20, hwnd, (HMENU)ID_RADIO_1, NULL, NULL);

            // 9. Bouton radio 2
            CreateWindow(TEXT("BUTTON"), TEXT("Option 2"), WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON, 120, 170, 100, 20, hwnd, (HMENU)ID_RADIO_2, NULL, NULL);

            // 10. Liste déroulante
            HWND hListBox = CreateWindow(TEXT("LISTBOX"), NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL, 10, 200, 200, 100, hwnd, (HMENU)ID_LISTBOX, NULL, NULL);
            SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("Élément 1"));
            SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("Élément 2"));
            SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("Élément 3"));
            break;
        }
        case WM_COMMAND: {
            // Gestion des clics sur les boutons
            switch (LOWORD(wParam)) {
                case ID_BUTTON_1:
                    MessageBox(hwnd, TEXT("Bouton 1 cliqué !"), TEXT("Information"), MB_OK);
                    break;
                case ID_BUTTON_2:
                    MessageBox(hwnd, TEXT("Bouton 2 cliqué !"), TEXT("Information"), MB_OK);
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
