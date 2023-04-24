#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <list>
#include "Player.h"

std::ostream& operator<<(std::ostream& os, const sf::TcpSocket& socket)
{
    os << '[' << socket.getRemoteAddress() << " : " << socket.getRemotePort() << ']';
    return os;
}

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