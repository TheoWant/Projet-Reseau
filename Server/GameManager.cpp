#include "framework.h"

GameManager::GameManager()
{
	sf::Vector2i pos;
	Ship* Carrier = new Ship(5, pos, false);
	Ship* Cruiser = new Ship(4, pos, false);
	Ship* ATB = new Ship(3, pos, false);
	Ship* Submarine = new Ship(3, pos, false);
	Ship* TorpedoBoat = new Ship(2, pos, false);
	shipsToPlace.push_back(Carrier);
	shipsToPlace.push_back(Cruiser);
	shipsToPlace.push_back(ATB);
	shipsToPlace.push_back(Submarine);
	shipsToPlace.push_back(TorpedoBoat);
}

void GameManager::SaveGrid(Grid* gridToSave, Grid* grid2ToSave)
{
	gridSave.str("");
	for (int col = 0; col < 10; col++)
	{
		for (int row = 0; row < 10; row++)
		{
			if (gridToSave->grid[row][col]->state == Node::base && !gridToSave->grid[row][col]->hasShip)
			{
				gridSave << "0";
			}
			else if (gridToSave->grid[row][col]->state == Node::miss)
			{
				gridSave << "M";
			}
			else if (gridToSave->grid[row][col]->state == Node::hit)
			{
				gridSave << "X";
			}
			else if (gridToSave->grid[row][col]->carrier == true)
			{
				gridSave << "5";
			}
			else if (gridToSave->grid[row][col]->cruiser == true)
			{
				gridSave << "4";
			}
			else if (gridToSave->grid[row][col]->atb == true)
			{
				gridSave << "3";
			}
			else if (gridToSave->grid[row][col]->submarine == true)
			{
				gridSave << "2";
			}
			else if (gridToSave->grid[row][col]->torpedo == true)
			{
				gridSave << "1";
			}
		}
		gridSave << "/";
	}
	for (int col = 0; col < 10; col++)
	{
		for (int row = 0; row < 10; row++)
		{
			if (grid2ToSave->grid[row][col]->state == Node::base && !grid2ToSave->grid[row][col]->hasShip)
			{
				gridSave << "0";
			}
			else if (grid2ToSave->grid[row][col]->state == Node::miss)
			{
				gridSave << "M";
			}
			else if (grid2ToSave->grid[row][col]->state == Node::hit)
			{
				gridSave << "X";
			}
			else if (grid2ToSave->grid[row][col]->carrier == true)
			{
				gridSave << "5";
			}
			else if (grid2ToSave->grid[row][col]->cruiser == true)
			{
				gridSave << "4";
			}
			else if (grid2ToSave->grid[row][col]->atb == true)
			{
				gridSave << "3";
			}
			else if (grid2ToSave->grid[row][col]->submarine == true)
			{
				gridSave << "2";
			}
			else if (grid2ToSave->grid[row][col]->torpedo == true)
			{
				gridSave << "1";
			}
		}
		gridSave << "/";
	}
	std::cout << gridSave.str();
}
