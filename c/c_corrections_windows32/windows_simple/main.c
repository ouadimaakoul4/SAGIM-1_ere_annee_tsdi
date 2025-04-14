#include <windows.h> // Inclure l'API Windows

// D�claration de la fonction de gestion des messages de la fen�tre
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Fonction principale (point d'entr�e de l'application)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Structure pour d�finir la classe de la fen�tre
    WNDCLASSEX wc;
    HWND hwnd; // Handle de la fen�tre
    MSG Msg;   // Structure pour stocker les messages

    // Remplir la structure WNDCLASSEX
    wc.cbSize        = sizeof(WNDCLASSEX); // Taille de la structure
    wc.style         = 0; // Style de la fen�tre (par d�faut)
    wc.lpfnWndProc   = WndProc; // Pointeur vers la fonction de gestion des messages
    wc.cbClsExtra    = 0; // Pas de m�moire suppl�mentaire pour la classe
    wc.cbWndExtra    = 0; // Pas de m�moire suppl�mentaire pour la fen�tre
    wc.hInstance     = hInstance; // Instance de l'application
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION); // Ic�ne par d�faut
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW); // Curseur par d�faut
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Couleur de fond de la fen�tre
    wc.lpszMenuName  = NULL; // Pas de menu
    wc.lpszClassName = TEXT("MaClasseDeFenetre"); // Nom de la classe de la fen�tre (utilisez TEXT pour les cha�nes TCHAR)
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION); // Petite ic�ne

    // Enregistrer la classe de la fen�tre
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, TEXT("�chec de l'enregistrement de la classe de fen�tre !"), TEXT("Erreur !"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Cr�er la fen�tre
    hwnd = CreateWindowEx(
        0, // Style �tendu (par d�faut)
        TEXT("MaClasseDeFenetre"), // Nom de la classe de la fen�tre (utilisez TEXT pour les cha�nes TCHAR)
        TEXT("Ma Premi�re Fen�tre"), // Titre de la fen�tre (utilisez TEXT pour les cha�nes TCHAR)
        WS_OVERLAPPEDWINDOW, // Style de la fen�tre (avec bordure, titre, etc.)
        CW_USEDEFAULT, CW_USEDEFAULT, // Position (par d�faut)
        500, 400, // Largeur et hauteur de la fen�tre
        NULL, NULL, hInstance, NULL); // Pas de parent, pas de menu, instance de l'application

    // V�rifier si la fen�tre a �t� cr��e avec succ�s
    if (hwnd == NULL) {
        MessageBox(NULL, TEXT("�chec de la cr�ation de la fen�tre !"), TEXT("Erreur !"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Afficher la fen�tre
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd); // Mettre � jour la fen�tre

    // Boucle de messages
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg); // Traduire les messages (comme les touches du clavier)
        DispatchMessage(&Msg);  // Envoyer les messages � la fonction WndProc
    }
    return Msg.wParam; // Retourner la valeur de sortie de l'application
}

// Fonction de gestion des messages de la fen�tre
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CLOSE: // Message re�u lorsque l'utilisateur clique sur le bouton "Fermer"
            DestroyWindow(hwnd); // D�truire la fen�tre
            break;
        case WM_DESTROY: // Message re�u lorsque la fen�tre est d�truite
            PostQuitMessage(0); // Quitter l'application
            break;
        default:
            // Traiter les autres messages avec la fonction par d�faut
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
