#pragma once


class Server {
public:
    Server();
    static DWORD WINAPI ServerThread(LPVOID lpParam);

    bool _run;
    WSADATA wsaData;
    SOCKET listenSocket;
    SOCKADDR_IN serverSocketInfo;

    static std::vector<SOCKET> players;
    bool waitForPlayer;
};
