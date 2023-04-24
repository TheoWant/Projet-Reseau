//#include "Server.h"
#include <iostream>
#include <string>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char** argv)
{
	if (argc < 2 || argc > 2) {
		std::cout << "./server [port]" << std::endl;
		return 84;
	}
    unsigned short port = std::stoi(argv[1]);

    SOCKET serverSocket;
    SOCKET clientSocket;
    SOCKADDR_IN serverSocketInfo;
    SOCKADDR_IN clientSocketInfo;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0) {} 

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    serverSocketInfo.sin_addr.s_addr = INADDR_ANY;
    serverSocketInfo.sin_family = AF_INET;
    serverSocketInfo.sin_port = htons(port);
    bind(serverSocket, (SOCKADDR*)&serverSocketInfo, sizeof(serverSocketInfo));
    listen(serverSocket, 0);

    while (1) /* Boucle infinie. Exercice : améliorez ce code. */
    {
        int sinsize = sizeof(clientSocketInfo);
        if ((clientSocket = accept(serverSocket, (SOCKADDR*)&clientSocketInfo, &sinsize)) != INVALID_SOCKET)
        {
            std::cout << "Client connected !" << std::endl;

            send(clientSocket, "Hello world!\r\n", 14, 0);
            closesocket(clientSocket);
        }
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;


	/*Server s(port);

	sf::Thread serverThread(&Server::startServer, &s);
	serverThread.launch();

	while (s.isRunning())
	{
		std::string string;
		std::getline(std::cin, string);
		if (string == "stop")
			s.stopServer();
	}*/
}