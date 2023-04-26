#pragma once
class GameManager
{
public:
	GameManager();
	void ReloadGrid(Grid* grid1,Grid* grid2);
	void SaveGrid(Grid* grid1, Grid* grid2);
	enum State 
	{
		shipPlacement,
		shipShooting,
		endGame
	};

	State state;

	std::vector<Ship*> shipsToPlace;
	std::string* gridGen;
	std::stringstream gridSave;
};

