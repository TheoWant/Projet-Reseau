#pragma once
class GameManager
{
public:
	GameManager();
	void SaveGrid(Grid* gridToSave, Grid* grid);
	enum State
	{
		shipPlacement,
		shipShooting,
		endGame
	};

	State state;

	std::vector<Grid*> grids;
	std::vector<Ship*> shipsToPlace;
	std::string gridGen;
	std::stringstream gridSave;
};

