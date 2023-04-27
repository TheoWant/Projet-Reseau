#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "framework.h"

#define WM_SOCKET WM_USER + 1

GameManager gameManager;

Player player1;
Player player2;

Grid* gridPlayer1 = new Grid();
Grid* gridPlayer2 = new Grid();

Server::Server()
{

}

extern "C" LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

DWORD WINAPI Server::ServerThread(LPVOID lpParam) {
    SOCKET clientSocket;
    SOCKADDR_IN clientSocketInfo;

    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = NULL;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        NULL,       // Instance handle
        NULL        // Additional application data
    );

    unsigned short port = 25565;

    Server* server = new Server();

    player1.playerTurn = true;

    gridPlayer1->CreateGrid();
    gridPlayer2->CreateGrid();

    gameManager.grids.push_back(gridPlayer1);
    gameManager.grids.push_back(gridPlayer2);

    gameManager.SaveGrid();

    int i = 0;

    server->listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server->listenSocket == INVALID_SOCKET)
    {
        std::cerr << "Error at listenSocket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }

    server->serverSocketInfo.sin_family = AF_INET;
    server->serverSocketInfo.sin_addr.s_addr = INADDR_ANY;
    server->serverSocketInfo.sin_port = htons(port);

    i = bind(server->listenSocket, (SOCKADDR*)&server->serverSocketInfo, sizeof(serverSocketInfo));
    if (i == SOCKET_ERROR)
    {
        std::cerr << "bind function failed with error: " << WSAGetLastError() << std::endl;
        i = closesocket(server->listenSocket);
        if (i == SOCKET_ERROR)
            std::cerr << "closesocket function failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }

    if (listen(server->listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cerr << "listen function failed with error: " << WSAGetLastError() << std::endl;
    }

    std::cout << "\033[30m\033[42mServer started.\033[0m" << std::endl;

    WSAAsyncSelect(server->listenSocket, hwnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE | FD_READ );

    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)server);

    MSG msg;

    while (GetMessage(&msg, hwnd, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    //PostMessage();
    return 0;
}

LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Server* server = (Server*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    SOCKET Accept;

    switch (uMsg)
    {

    case WM_SOCKET:
        // Determine whether an error occurred on the
        // socket by using the WSAGETSELECTERROR() macro
        if (WSAGETSELECTERROR(lParam))
        {
            // Display the error and close the socket
            closesocket((SOCKET)wParam);
            break;
        }
        // Determine what event occurred on the socket
        switch (WSAGETSELECTEVENT(lParam))
        {
            case FD_ACCEPT:
                // Accept an incoming connection
                Accept = accept(wParam, NULL, NULL);
                // Prepare accepted socket for read, write, and close notification
                WSAAsyncSelect(Accept, hwnd, WM_SOCKET, FD_READ | FD_CLOSE);
                std::cout << "Client connected !" << std::endl;
                break;

            case FD_READ:
            {
                // Receive data from the socket in wParam
                char buffer[1024];
                int bytesReceived = recv(wParam, buffer, sizeof(buffer), 0);
                std::string receivedMessage(buffer, bytesReceived);
                std::cout << "Message recu du client : " << receivedMessage << std::endl;

                std::string tmpString;
                std::vector<std::string> segList;
                char separator = '/';
                for (int i = 0; i < receivedMessage.size(); i++) {
                    if (buffer[i] != separator)
                    {
                        tmpString += buffer[i];
                    }
                    else
                    {
                        segList.push_back(tmpString);
                        tmpString.clear();
                    }
                }

                //-----------|TO DO|-------------
                // Si dans la pose de bateau
                // Check quel client a joué
                // Check si la pose du bateau est correct
                // Si dans la phase d'attaque
                // Check la case touché
                // Modifier la string de réponse
                // Send la string

                break;
            }

            case FD_CLOSE:
                // The connection is now closed
                closesocket((SOCKET)wParam);
                break;
        }
        break;
    }

    //for (auto& player : players)
    //{

    //    char buffer[1024];
    //    int bytesReceived = recv(player.getClientSocket(), buffer, sizeof(buffer), 0);

    //    if (bytesReceived == SOCKET_ERROR)
    //    {
    //        std::cerr << "Error receiving data from client: " << WSAGetLastError() << std::endl;
    //        continue;
    //    }
    //    else if (bytesReceived == 0)
    //    {
    //        // connexion fermée
    //        std::cout << "Client disconnected." << std::endl;
    //        continue;
    //    }
    //    else
    //    {
    //        // Message reçu
    //        system("CLS");
    //        std::string receivedMessage(buffer, bytesReceived);
    //        std::cout << "Message recu du client : " << receivedMessage << std::endl;
    //    }
    //}
    return DefWindowProc(hwnd,uMsg,wParam,lParam);
}
//int sinsize = sizeof(clientSocketInfo);
//if ((clientSocket = accept(server->listenSocket, (SOCKADDR*)&clientSocketInfo, &sinsize)) != INVALID_SOCKET) // si il y a un client
//{
//    server->players.push_back(Client(clientSocket, clientSocketInfo)); // on ajoute le client a la liste des joueurs
//    std::cout << "Client connected !" << std::endl;
//    std::string s = "Hello world! there is " + std::to_string(server->players.size()) + " player connected!\r\n";
//    send(clientSocket, s.c_str(), s.size(), 0); // on envoie un message au client
//
//    // Boucler sur chaque client connecté
//
//    // closesocket(clientSocket); // on ferme la socket du client (temporaire, faut enlever ca, le metre autre pars)
//}