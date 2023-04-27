#pragma once

class Player
{
public:
	Player();
	~Player();
	std::string playerName;
	bool playerTurn;
	SOCKET socket;
};

