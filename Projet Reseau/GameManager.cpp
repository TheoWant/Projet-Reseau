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


void GameManager::ReloadGrid(Grid* grid1,Grid* grid2)
{
	int index = 0;
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (gridGen[index] == "0")
			{
				grid1->grid[x][y]->state = Node::base;
				grid1->grid[x][y]->hasShip = false;
			}
			else if (gridGen[index] == "1")
			{
				grid1->grid[x][y]->hasShip = true;
				grid1->grid[x][y]->torpedo = true;
			}
			else if (gridGen[index] == "2")
			{
				grid1->grid[x][y]->hasShip = true;
				grid1->grid[x][y]->submarine = true;
			}
			else if (gridGen[index] == "3")
			{
				grid1->grid[x][y]->hasShip = true;
				grid1->grid[x][y]->atb = true;
			}
			else if (gridGen[index] == "4")
			{
				grid1->grid[x][y]->hasShip = true;
				grid1->grid[x][y]->cruiser = true;
			}
			else if (gridGen[index] == "5")
			{
				grid1->grid[x][y]->hasShip = true;
				grid1->grid[x][y]->carrier = true;
			}
			else if (gridGen[index] == "X")
			{
				grid1->grid[x][y]->state = Node::hit;
			}
			else if (gridGen[index] == "M")
			{
				grid1->grid[x][y]->state = Node::miss;
			}
		}
	}
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (gridGen[index] == "0")
			{
				grid2->grid[x][y]->state = Node::base;
				grid2->grid[x][y]->hasShip = false;
			}
			else if (gridGen[index] == "1")
			{
				grid2->grid[x][y]->hasShip = true;
				grid2->grid[x][y]->torpedo = true;
			}
			else if (gridGen[index] == "2")
			{
				grid2->grid[x][y]->hasShip = true;
				grid2->grid[x][y]->submarine = true;
			}
			else if (gridGen[index] == "3")
			{
				grid2->grid[x][y]->hasShip = true;
				grid2->grid[x][y]->atb = true;
			}
			else if (gridGen[index] == "4")
			{
				grid2->grid[x][y]->hasShip = true;
				grid2->grid[x][y]->cruiser = true;
			}
			else if (gridGen[index] == "5")
			{
				grid2->grid[x][y]->hasShip = true;
				grid2->grid[x][y]->carrier = true;
			}
			else if (gridGen[index] == "X")
			{
				grid2->grid[x][y]->state = Node::hit;
			}
			else if (gridGen[index] == "M")
			{
				grid2->grid[x][y]->state = Node::miss;
			}
		}
	}
}

void GameManager::SaveGrid(Grid* grid1,Grid* grid2)
{
	gridSave.str("");
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (grid1->grid[x][y]->state == Node::base && !grid1->grid[x][y]->hasShip)
			{
				gridSave << "0";
			}
			else if (grid1->grid[x][y]->state == Node::hit)
			{
				gridSave << "X";
			}
			else if (grid1->grid[x][y]->state == Node::miss)
			{
				gridSave << "M";
			}
			else if (grid1->grid[x][y]->state == Node::base && grid1->grid[x][y]->hasShip && grid1->grid[x][y]->carrier)
			{
				gridSave << "5";
			}
			else if (grid1->grid[x][y]->state == Node::base && grid1->grid[x][y]->hasShip && grid1->grid[x][y]->cruiser)
			{
				gridSave << "4";
			}
			else if (grid1->grid[x][y]->state == Node::base && grid1->grid[x][y]->hasShip && grid1->grid[x][y]->atb)
			{
				gridSave << "3";
			}
			else if (grid1->grid[x][y]->state == Node::base && grid1->grid[x][y]->hasShip && grid1->grid[x][y]->submarine)
			{
				gridSave << "2";
			}
			else if (grid1->grid[x][y]->state == Node::base && grid1->grid[x][y]->hasShip && grid1->grid[x][y]->torpedo)
			{
				gridSave << "1";
			}
		}
		gridSave << "/";
	}
	gridSave << "}";
	gridSave << "{";
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (grid2->grid[x][y]->state == Node::base && !grid2->grid[x][y]->hasShip)
			{
				gridSave << "0";
			}
			else if (grid2->grid[x][y]->state == Node::hit)
			{
				gridSave << "X";
			}
			else if (grid2->grid[x][y]->state == Node::miss)
			{
				gridSave << "M";
			}
			else if (grid2->grid[x][y]->state == Node::base && grid2->grid[x][y]->hasShip && grid2->grid[x][y]->carrier)
			{
				gridSave << "5";
			}
			else if (grid2->grid[x][y]->state == Node::base && grid2->grid[x][y]->hasShip && grid2->grid[x][y]->cruiser)
			{
				gridSave << "4";
			}
			else if (grid2->grid[x][y]->state == Node::base && grid2->grid[x][y]->hasShip && grid2->grid[x][y]->atb)
			{
				gridSave << "3";
			}
			else if (grid2->grid[x][y]->state == Node::base && grid2->grid[x][y]->hasShip && grid2->grid[x][y]->submarine)
			{
				gridSave << "2";
			}
			else if (grid2->grid[x][y]->state == Node::base && grid2->grid[x][y]->hasShip && grid2->grid[x][y]->torpedo)
			{
				gridSave << "1";
			}
		}
		gridSave << "/";
	}
	gridSave << "}";
	std::cout << gridSave.str();
}
