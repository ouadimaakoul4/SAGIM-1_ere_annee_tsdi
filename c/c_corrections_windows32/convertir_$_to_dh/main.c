#include <windows.h>
#include <tchar.h>
#include <stdio.h>

// Constantes pour les ID des contrôles
#define ID_USD_EDIT 1
#define ID_CONVERT_BUTTON 2
#define ID_MAD_STATIC 3

// Taux de change fixe : 1 USD = 9.5 MAD
#define EXCHANGE_RATE 9.5

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
    wc.lpszClassName = TEXT("ConverterClass");
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, TEXT("Échec de l'enregistrement de la classe de fenêtre !"), TEXT("Erreur !"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Création de la fenêtre
    hwnd = CreateWindowEx(0, TEXT("ConverterClass"), TEXT("Convertisseur USD vers MAD"),
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 200, NULL, NULL, hInstance, NULL);

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
            CreateWindow(TEXT("STATIC"), TEXT("Montant en USD ($):"), WS_VISIBLE | WS_CHILD, 10, 10, 150, 20, hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 160, 10, 100, 20, hwnd, (HMENU)ID_USD_EDIT, NULL, NULL);

            CreateWindow(TEXT("BUTTON"), TEXT("Convertir"), WS_VISIBLE | WS_CHILD, 10, 40, 100, 30, hwnd, (HMENU)ID_CONVERT_BUTTON, NULL, NULL);

            CreateWindow(TEXT("STATIC"), TEXT("Montant en MAD (DH):"), WS_VISIBLE | WS_CHILD, 10, 80, 150, 20, hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("STATIC"), TEXT("0.00 DH"), WS_VISIBLE | WS_CHILD, 160, 80, 100, 20, hwnd, (HMENU)ID_MAD_STATIC, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == ID_CONVERT_BUTTON) {
                TCHAR usdStr[100];
                GetWindowText(GetDlgItem(hwnd, ID_USD_EDIT), usdStr, 100);

                // Convertir la chaîne en nombre
                double usd = _tcstod(usdStr, NULL);

                // Calculer le montant en MAD
                double mad = usd * EXCHANGE_RATE;

                // Afficher le résultat
                TCHAR madStr[100];
                _stprintf(madStr, TEXT("%.2f DH"), mad);
                SetWindowText(GetDlgItem(hwnd, ID_MAD_STATIC), madStr);
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
