#pragma once

#include <vector>
#include "Player.h"

class Server {
public:
    Server(unsigned short port);

private:
    bool _run;
    WSADATA wsaData;
    SOCKET listenSocket;
    SOCKADDR_IN serverSocketInfo;

    std::vector<Player> players;
    bool waitForPlayer;
};
