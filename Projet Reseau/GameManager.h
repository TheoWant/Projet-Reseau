#pragma once
class GameManager
{
public:
	GameManager();

	enum State 
	{
		shipPlacement,
		shipShooting,
		endGame
	};

	State state;

	std::vector<Ship*> shipsToPlace;
};

