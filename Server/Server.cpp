#include "Server.h"

std::ostream& operator<<(std::ostream& os, const sf::TcpSocket& socket)
{
    os << '[' << socket.getRemoteAddress() << " : " << socket.getRemotePort() << ']';
    return os;
}

Server::Server(unsigned short port)
{
	_run = true;
	if (_listener.listen(port) != sf::Socket::Done)
		exit(84);
	_selector.add(_listener);
}

void Server::stopServer()
{
	_run = false;
}

void Server::startServer()
{
    _run = true;
    std::cout << "\033[30m\033[42mServer started.\033[0m" << std::endl;
    while (_run) {
        if (_selector.wait(sf::seconds(1))) {
            if (_selector.isReady(_listener)) {
                Player* p = new Player;
                if (_listener.accept(p->getSocket()) == sf::Socket::Done) {
                    _selector.add(p->getSocket());
                    _Players.push_back(p);
                    std::cout << "\033[32mNew connection.\033[0m " << p->getSocket() << std::endl;
                }
                else
                    delete p;
            }
            else {
                for (std::list<Player*>::iterator it = _Players.begin(); it != _Players.end(); it++) {
                    Player& p = **it;
                    if (_selector.isReady(p.getSocket())) {
                        sf::Packet packet;
                        if (checkStatus(p.getSocket().receive(packet), p.getSocket())) {

                            /*std::vector<std::string> s = extractPacket(packet);
                            p.setUuid(s[0]);
                            if (s[1] == "queue" || s[1] == "connecting")
                                p.setState(s[1]);
                            else if (p.getEnemyUuid() != "")
                                sendToEnemy(p, s[1]);
                            std::cout << p.getUuid() << " | ";
                            if (p.getState() == "white")
                                std::cout << p.getState() << " | " << s[1] << std::endl;
                            else if (p.getState() == "black")
                                std::cout << "\033[47m\033[30m" << p.getState() << "\033[0m | " << s[1] << std::endl;
                            else if (p.getState() == "queue")
                                std::cout << "\033[33m" << p.getState() << "\033[0m | " << s[1] << std::endl;
                            else if (p.getState() == "connecting")
                                std::cout << "\033[32m" << p.getState() << "\033[0m | " << s[1] << std::endl;*/

                        }
                        else {
                            _selector.remove(p.getSocket());
                            _Players.erase(it);
                            delete& p;
                            break;
                        }
                    }
                }
            }
        }
        manageGames();
    }
    disconnectAll();
}

bool Server::isRunning() const
{
    return _run;
}

void Server::sendToEnemy(Player& p, std::string move)
{
    sf::Packet packet;
    packet << move;

    for (std::list<Player*>::iterator it = _Players.begin(); it != _Players.end(); it++) {
        Player& enemy = **it;
        if (enemy.getUuid() == p.getEnemyUuid())
            enemy.getSocket().send(packet);
    }
}

void Server::manageGames()
{
    /*sf::Packet pw;
    pw << "white";

    sf::Packet pb;
    pb << "black";

    for (std::list<Player*>::iterator it = _Players.begin(); it != _Players.end(); it++) {
        Player& playerA = **it;
        if (playerA.getState() == "queue")
            for (std::list<Player*>::iterator ite = _Players.begin(); ite != _Players.end(); ite++) {
                Player& playerB = **ite;
                if (playerB.getState() == "queue")
                    if (playerA.getUuid().compare(playerB.getUuid()) != 0) {
                        std::cout << "\033[35mgame started between\033[0m " << playerA.getSocket() << " \033[35mand\033[0m " << playerB.getSocket() << std::endl;
                        long side = random() % 2;
                        if (side == 0) {
                            playerA.setState("white");
                            playerB.setState("black");
                        }
                        else {
                            playerA.setState("black");
                            playerB.setState("white");
                        }

                        playerA.setEnemyUuid(playerB.getUuid());
                        playerB.setEnemyUuid(playerA.getUuid());

                        if (side == 0) {
                            playerA.getSocket().send(pw);
                            playerB.getSocket().send(pb);
                        }
                        else {
                            playerA.getSocket().send(pb);
                            playerB.getSocket().send(pw);
                        }
                    }
            }
    }*/
}

void Server::disconnectAll()
{
    for (std::list<Player*>::iterator it = _Players.begin(); it != _Players.end(); it++) {
        Player& player = **it;
        _selector.remove(player.getSocket());
        player.getSocket().disconnect();
        delete& player.getSocket();
    }
    _selector.remove(_listener);
    _listener.close();
}

std::vector<std::string> Server::extractPacket(sf::Packet p)
{
    std::vector<std::string> r;
    std::string s;

    while (p >> s)
        r.push_back(s);
    return r;
}

bool Server::checkStatus(sf::Socket::Status status, sf::TcpSocket& socket)
{
    switch (status)
    {
    case sf::Socket::Done:
        std::cout << "\033[32mThe socket has sent / received data.\033[0m " << socket << std::endl;
        return true;
    case sf::Socket::NotReady:
        std::cout << "\033[31mThe socket is not ready to send / receive data yet.\033[0m " << socket << std::endl;
        return false;
    case sf::Socket::Partial:
        std::cout << "\033[33mThe socket sent a part of the data.\033[0m " << socket << std::endl;
        return false;
    case sf::Socket::Disconnected:
        std::cout << "\033[31mThe TCP socket has been disconnected.\033[0m " << socket << std::endl;
        return false;
    case sf::Socket::Error:
        std::cout << "\033[41mAn unexpected error happened.\033[0m " << socket << std::endl;
        return false;
    }
    return false;
}