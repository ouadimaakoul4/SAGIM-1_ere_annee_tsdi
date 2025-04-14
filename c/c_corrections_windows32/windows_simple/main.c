#include <windows.h> // Inclure l'API Windows

// Déclaration de la fonction de gestion des messages de la fenêtre
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Fonction principale (point d'entrée de l'application)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Structure pour définir la classe de la fenêtre
    WNDCLASSEX wc;
    HWND hwnd; // Handle de la fenêtre
    MSG Msg;   // Structure pour stocker les messages

    // Remplir la structure WNDCLASSEX
    wc.cbSize        = sizeof(WNDCLASSEX); // Taille de la structure
    wc.style         = 0; // Style de la fenêtre (par défaut)
    wc.lpfnWndProc   = WndProc; // Pointeur vers la fonction de gestion des messages
    wc.cbClsExtra    = 0; // Pas de mémoire supplémentaire pour la classe
    wc.cbWndExtra    = 0; // Pas de mémoire supplémentaire pour la fenêtre
    wc.hInstance     = hInstance; // Instance de l'application
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION); // Icône par défaut
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW); // Curseur par défaut
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Couleur de fond de la fenêtre
    wc.lpszMenuName  = NULL; // Pas de menu
    wc.lpszClassName = TEXT("MaClasseDeFenetre"); // Nom de la classe de la fenêtre (utilisez TEXT pour les chaînes TCHAR)
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION); // Petite icône

    // Enregistrer la classe de la fenêtre
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, TEXT("Échec de l'enregistrement de la classe de fenêtre !"), TEXT("Erreur !"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Créer la fenêtre
    hwnd = CreateWindowEx(
        0, // Style étendu (par défaut)
        TEXT("MaClasseDeFenetre"), // Nom de la classe de la fenêtre (utilisez TEXT pour les chaînes TCHAR)
        TEXT("Ma Première Fenêtre"), // Titre de la fenêtre (utilisez TEXT pour les chaînes TCHAR)
        WS_OVERLAPPEDWINDOW, // Style de la fenêtre (avec bordure, titre, etc.)
        CW_USEDEFAULT, CW_USEDEFAULT, // Position (par défaut)
        500, 400, // Largeur et hauteur de la fenêtre
        NULL, NULL, hInstance, NULL); // Pas de parent, pas de menu, instance de l'application

    // Vérifier si la fenêtre a été créée avec succès
    if (hwnd == NULL) {
        MessageBox(NULL, TEXT("Échec de la création de la fenêtre !"), TEXT("Erreur !"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Afficher la fenêtre
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd); // Mettre à jour la fenêtre

    // Boucle de messages
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg); // Traduire les messages (comme les touches du clavier)
        DispatchMessage(&Msg);  // Envoyer les messages à la fonction WndProc
    }
    return Msg.wParam; // Retourner la valeur de sortie de l'application
}

// Fonction de gestion des messages de la fenêtre
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CLOSE: // Message reçu lorsque l'utilisateur clique sur le bouton "Fermer"
            DestroyWindow(hwnd); // Détruire la fenêtre
            break;
        case WM_DESTROY: // Message reçu lorsque la fenêtre est détruite
            PostQuitMessage(0); // Quitter l'application
            break;
        default:
            // Traiter les autres messages avec la fonction par défaut
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
