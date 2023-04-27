#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "framework.h"



#define WM_SOCKET WM_USER + 1

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

//    ShowWindow(hwnd,1);

    unsigned short port = 25565;

    Server* server = new Server();

    GameManager gameManager;

    Player player1;
    player1.playerTurn = true;

    Player player2;

    Grid* gridPlayer1;
    Grid* gridPlayer2;

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

    i = bind(server->listenSocket, (SOCKADDR*)&server->serverSocketInfo, sizeof(&server->serverSocketInfo));
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

    MSG msg;
    BOOL bRet;

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
    SOCKET Accept;
	SOCKADDR_IN clientSocketInfo;

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
                Server::players.push_back(Accept);
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
                break;
            }

            case FD_CLOSE:
                // The connection is now closed
                closesocket((SOCKET)wParam);
                break;
        }
        break;
    }
    return DefWindowProc(hwnd,uMsg,wParam,lParam);
}