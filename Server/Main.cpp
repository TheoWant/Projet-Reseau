#include "Server.h"

int main(int argc, char** argv)
{
    if (argc < 2 || argc > 2) {
        std::cout << "./server [port]" << std::endl;
        return 84;
    }
    unsigned short port = std::stoi(argv[1]);

    Server s(port);

    sf::Thread serverThread(&Server::startServer, &s);
    serverThread.launch();

    while (s.isRunning())
    {
        std::string string;
        std::getline(std::cin, string);
        if (string == "quit")
            s.stopServer();
    }
}