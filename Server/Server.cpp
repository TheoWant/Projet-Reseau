#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "common.h"



#define WM_SOCKET WM_USER + 1

Server::Server()
{

    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET)
    {
		std::cerr << "Error at listenSocket: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}

    serverSocketInfo.sin_family = AF_INET;
    serverSocketInfo.sin_addr.s_addr = INADDR_ANY;
    serverSocketInfo.sin_port = htons(port);

    i = bind(listenSocket, (SOCKADDR*)&serverSocketInfo, sizeof(serverSocketInfo));
    if (i == SOCKET_ERROR)
    {
		std::cerr << "bind function failed with error: " << WSAGetLastError() << std::endl;
		i = closesocket(listenSocket);
        if (i == SOCKET_ERROR)
			std::cerr << "closesocket function failed with error: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
        std::cerr << "listen function failed with error: " << WSAGetLastError() << std::endl;
    }

    std::cout << "\033[30m\033[42mServer started.\033[0m" << std::endl;


    // ==================== pas fini ====================
    // faut faire une queue de client si il y en a 2 ou plus
    // faire un thread qui gere la game entre les 2

    
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

    ShowWindow(hwnd,1);

    Server* server = reinterpret_cast<Server*>(lpParam);

    WSAAsyncSelect(server->listenSocket, hwnd, WM_APP + 1, FD_ACCEPT | FD_CLOSE | FD_READ );

    int sinsize = sizeof(clientSocketInfo);
    if ((clientSocket = accept(server->listenSocket, (SOCKADDR*)&clientSocketInfo, &sinsize)) != INVALID_SOCKET) // si il y a un client
    {
        //PostMessage()
        //WSAAsyncSelect
        server->players.push_back(Client(clientSocket, clientSocketInfo)); // on ajoute le client a la liste des joueurs
        std::cout << "Client connected !" << std::endl;
        std::string s = "Hello world! there is " + std::to_string(server->players.size()) + " player connected!\r\n";
        send(clientSocket, s.c_str(), s.size(), 0); // on envoie un message au client

        // Boucler sur chaque client connecté

        //closesocket(clientSocket); // on ferme la socket du client (temporaire, faut enlever ca, le metre autre pars)
    }

    LPMSG msg = nullptr;
    BOOL bRet;

    while ((bRet = GetMessage(msg, hwnd, 0, 0)) != 0)
    {
        if (bRet == -1)
        {
            // handle the error and possibly exit
        }
        else
        {
            TranslateMessage(msg);
            DispatchMessage(msg);
        }
    }
    //PostMessage();
    return 0;
}

LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
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
                WSAAsyncSelect(Accept, hwnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
                break;
            case FD_READ:
                // Receive data from the socket in wParam
                break;
            case FD_WRITE:
                // The socket in wParam is ready for sending data
                break;

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
