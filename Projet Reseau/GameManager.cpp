#include "framework.h"

GameManager::GameManager()
{
	sf::Vector2i pos;
	Ship* Carrier = new Ship(5,pos , false);
	Ship* Cruiser = new Ship(4,pos , false);
	Ship* ATB = new Ship(3,pos , false);
	Ship* Submarine = new Ship(3,pos , false);
	Ship* TorpedoBoat = new Ship(2,pos , false);
	shipsToPlace.push_back(Carrier);
	shipsToPlace.push_back(Cruiser);
	shipsToPlace.push_back(ATB);
	shipsToPlace.push_back(Submarine);
	shipsToPlace.push_back(TorpedoBoat);
}


void GameManager::ReloadGrid()
{
	int indexOfGrid = 0;
	for (int i = 0; i < gridGen.size(); i++)
	{
		int x = i % 11;
		int y = (int)floor(i / 11) - indexOfGrid * 11;
		if (i == gridGen.size()/2)
		{
			indexOfGrid++;
		}
		if (gridGen[i] == '0')
		{
			grids[indexOfGrid]->grid[x][y]->state = Node::base;
			grids[indexOfGrid]->grid[x][y]->hasShip = false;
		}
		else if (gridGen[i] == '1')
		{
			grids[indexOfGrid]->grid[x][y]->state = Node::base;
			grids[indexOfGrid]->grid[x][y]->hasShip = true;
			grids[indexOfGrid]->grid[x][y]->torpedo = true;
		}
		else if (gridGen[i] == '2')
		{
			grids[indexOfGrid]->grid[x][y]->state = Node::base;
			grids[indexOfGrid]->grid[x][y]->hasShip = true;
			grids[indexOfGrid]->grid[x][y]->submarine = true;
		}
		else if (gridGen[i] == '3')
		{
			grids[indexOfGrid]->grid[x][y]->state = Node::base;
			grids[indexOfGrid]->grid[x][y]->hasShip = true;
			grids[indexOfGrid]->grid[x][y]->atb = true;
		}
		else if (gridGen[i] == '4')
		{
			grids[indexOfGrid]->grid[x][y]->state = Node::base;
			grids[indexOfGrid]->grid[x][y]->hasShip = true;
			grids[indexOfGrid]->grid[x][y]->cruiser = true;
		}
		else if (gridGen[i] == '5')
		{
			grids[indexOfGrid]->grid[x][y]->state = Node::base;
			grids[indexOfGrid]->grid[x][y]->hasShip = true;
			grids[indexOfGrid]->grid[x][y]->carrier = true;
		}
		else if (gridGen[i] == 'M')
		{
			grids[indexOfGrid]->grid[x][y]->state = Node::miss;
			grids[indexOfGrid]->grid[x][y]->hasShip = false;
		}
		else if (gridGen[i] == 'X')
		{
			grids[indexOfGrid]->grid[x][y]->state = Node::hit;
			grids[indexOfGrid]->grid[x][y]->hasShip = true;
		}
	}
}

void GameManager::SaveGrid()
{
	gridSave.str("");
	for (int gridCheck = 0; gridCheck < grids.size(); gridCheck++)
	{
		Grid* gridToSave = grids[gridCheck];
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
	}
	std::cout << gridSave.str();
}
