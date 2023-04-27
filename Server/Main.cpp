#include "common.h"

int main(int argc, char** argv)
{
	if (argc < 2 || argc > 2) {
		std::cout << "./server [port]" << std::endl;
		return 84;
	}
    unsigned short port = std::stoi(argv[1]);

    WSADATA wsaData;

    int i = 0;
    i = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (i != NO_ERROR)
    {
        std::cerr << "Error at WSAStartup: " << i << std::endl;
        return;
    }

    HANDLE hThread;
    DWORD dwThreadId;
    //hThread = CreateThread(NULL, 0, Server::ServerThread, this, 0, &dwThreadId);

    return 0;
}