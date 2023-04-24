#ifndef SERVER_H_
#define SERVER_H_

#include <SFML/Network.hpp>
#include <iostream>
#include <list>
#include "Player.h"

class Server {
public:
    Server(unsigned short port);

    void stopServer();
    void startServer();
    bool isRunning() const;

private:
    bool _run;
    sf::TcpListener _listener;
    sf::SocketSelector _selector;
    std::list<Player*> _Players;

    void sendToEnemy(Player& p, std::string move);
    void manageGames();
    void disconnectAll();
    std::vector<std::string> extractPacket(sf::Packet p);
    bool checkStatus(sf::Socket::Status status, sf::TcpSocket& socket);
};

#endif /* !SERVER_H_ */