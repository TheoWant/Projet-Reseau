#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "Server.h"
#include <iostream>
#include <Windows.h>

Server::Server(unsigned short port)
{
	_run = true;

    int i = 0;
    i = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (i != NO_ERROR)
    {
        std::cerr << "Error at WSAStartup: " << i << std::endl;
        return;
    }

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
    
    


    while (_run)
    {
        HANDLE hThread;
        DWORD dwThreadId;
        hThread = CreateThread(NULL, 0, ServerThread, this, 0, &dwThreadId);

        //std::cout << "ca passe ?" << std::endl;

        for (auto& player : players)
        {

            char buffer[1024];
            int bytesReceived = recv(player.getClientSocket(), buffer, sizeof(buffer), 0);

            if (bytesReceived == SOCKET_ERROR)
            {
                std::cerr << "Error receiving data from client: " << WSAGetLastError() << std::endl;
                continue;
            }
            else if (bytesReceived == 0)
            {
                // connexion fermée
                std::cout << "Client disconnected." << std::endl;
                continue;
            }
            else
            {
                // Message reçu
                std::string receivedMessage(buffer, bytesReceived);
                std::cout << "Message recu du client : " << receivedMessage << std::endl;
            }
        }
	}
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

    Server* server = reinterpret_cast<Server*>(lpParam);

    WSAAsyncSelect(server->listenSocket, hwnd, WM_APP + 1, FD_ACCEPT | FD_CLOSE );

    int sinsize = sizeof(clientSocketInfo);
    if ((clientSocket = accept(server->listenSocket, (SOCKADDR*)&clientSocketInfo, &sinsize)) != INVALID_SOCKET) // si il y a un client
    {
        //PostMessage()
        //WSAAsyncSelect
        server->players.push_back(Player(clientSocket, clientSocketInfo)); // on ajoute le client a la liste des joueurs
        std::cout << "Client connected !" << std::endl;
        std::string s = "Hello world! there is " + std::to_string(server->players.size()) + " player connected!\r\n";
        send(clientSocket, s.c_str(), s.size(), 0); // on envoie un message au client

        // Boucler sur chaque client connecté

        //closesocket(clientSocket); // on ferme la socket du client (temporaire, faut enlever ca, le metre autre pars)
    }
    return 0;
}

LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return LRESULT();
}
