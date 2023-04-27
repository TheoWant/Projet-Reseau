#pragma once
class GameManager
{
public:
	GameManager();
	void ReloadGrid();
	void SaveGrid();
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

