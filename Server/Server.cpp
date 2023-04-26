#include "Server.h"
#include <iostream>

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
        SOCKET clientSocket;
        SOCKADDR_IN clientSocketInfo;

		int sinsize = sizeof(clientSocketInfo);
        if ((clientSocket = accept(listenSocket, (SOCKADDR*)&clientSocketInfo, &sinsize)) != INVALID_SOCKET) // si il y a un client
        {
            //PostMessage()
            //WSAAsyncSelect
            players.push_back(Player(clientSocket, clientSocketInfo)); // on ajoute le client a la liste des joueurs
			std::cout << "Client connected !" << std::endl;
            std::string s = "Hello world! there is " + std::to_string(players.size()) + " player connected!\r\n";
			send(clientSocket, s.c_str(), s.size(), 0); // on envoie un message au client
			closesocket(clientSocket); // on ferme la socket du client (temporaire, faut enlever ca, le metre autre pars)
		}
	}
}