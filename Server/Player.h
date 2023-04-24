#pragma once

#include <winsock2.h>
#include <string>

class Player {
public:
	Player(SOCKET clientSocket, SOCKADDR_IN clientSocketInfo) : _clientSocket(clientSocket), _clientSocketInfo(clientSocketInfo) {};
	SOCKET getClientSocket() const { return _clientSocket; }
	SOCKADDR_IN getClientSocketInfo() const { return _clientSocketInfo; }
	
private:
	SOCKET _clientSocket;
	SOCKADDR_IN _clientSocketInfo;
};