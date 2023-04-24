#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Network/TcpSocket.hpp>
#include <string>

class Player {
public:
	sf::TcpSocket& getSocket() { return _socket; }
	void setState(const std::string s) { _state = s; }

	std::string getState() const { return _state; }
	void setName(const std::string name) { _name = name; }

	std::string getName() const { return _name; }
	void setUuid(const std::string uuid) { _uuid = uuid; }

	std::string getUuid() const { return _uuid; }

	void setEnemyUuid(const std::string uuid) { _enemyUuid = uuid; }
	std::string getEnemyUuid() const { return _enemyUuid; }

private:
	sf::TcpSocket _socket;
	std::string _state;
	std::string _name;
	std::string _uuid;
	std::string _enemyUuid;
};

#endif /* !PLAYER_H_ */