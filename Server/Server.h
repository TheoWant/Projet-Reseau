#pragma once

#include <vector>
#include "Player.h"

class Server {
public:
    Server(unsigned short port);
    static DWORD WINAPI MaFonctionDeThread(LPVOID lpParam);
    SOCKET GetListenSocket() { return listenSocket; }
    std::vector<Player> GetPlayers() { return players; }

private:
    bool _run;
    WSADATA wsaData;
    SOCKET listenSocket;
    SOCKADDR_IN serverSocketInfo;

    std::vector<Player> players;
    bool waitForPlayer;
};
