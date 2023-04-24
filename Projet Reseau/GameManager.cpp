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
	for (int y = 1; y < 11; y++)
	{
		for (int x = 1; x <= 11; x++)
		{
			if (gridGen[index] == '0')
			{
				grid1->grid[y][x]->state = Node::base;
				grid1->grid[y][x]->hasShip = false;
			}
			else if (gridGen[index] == '1')
			{
				grid1->grid[y][x]->hasShip = true;
				grid1->grid[y][x]->torpedo = true;
			}
			else if (gridGen[index] == '2')
			{
				grid1->grid[y][x]->hasShip = true;
				grid1->grid[y][x]->submarine = true;
			}
			else if (gridGen[index] == '3')
			{
				grid1->grid[y][x]->hasShip = true;
				grid1->grid[y][x]->atb = true;
			}
			else if (gridGen[index] == '4')
			{
				grid1->grid[y][x]->hasShip = true;
				grid1->grid[y][x]->cruiser = true;
			}
			else if (gridGen[index] == '5')
			{
				grid1->grid[y][x]->hasShip = true;
				grid1->grid[y][x]->carrier = true;
			}
			else if (gridGen[index] == 'X')
			{
				grid1->grid[y][x]->state = Node::hit;
			}
			else if (gridGen[index] == 'M')
			{
				grid1->grid[y][x]->state = Node::miss;
			}
		}
	}
	for (int y = 1; y < 11; y++)
	{
		for (int x = 1; x <= 11; x++)
		{
			if (gridGen[index] == '0')
			{
				grid2->grid[y][x]->state = Node::base;
				grid2->grid[y][x]->hasShip = false;
			}
			else if (gridGen[index] == '1')
			{
				grid2->grid[y][x]->hasShip = true;
				grid2->grid[y][x]->torpedo = true;
			}
			else if (gridGen[index] == '2')
			{
				grid2->grid[y][x]->hasShip = true;
				grid2->grid[y][x]->submarine = true;
			}
			else if (gridGen[index] == '3')
			{
				grid2->grid[y][x]->hasShip = true;
				grid2->grid[y][x]->atb = true;
			}
			else if (gridGen[index] == '4')
			{
				grid2->grid[y][x]->hasShip = true;
				grid2->grid[y][x]->cruiser = true;
			}
			else if (gridGen[index] == '5')
			{
				grid2->grid[y][x]->hasShip = true;
				grid2->grid[y][x]->carrier = true;
			}
			else if (gridGen[index] == 'X')
			{
				grid2->grid[y][x]->state = Node::hit;
			}
			else if (gridGen[index] == 'M')
			{
				grid2->grid[y][x]->state = Node::miss;
			}
		}
	}
}

void GameManager::SaveGrid(Grid* grid1,Grid* grid2)
{
	gridGen = new char[255];
	int index = 0;
	for (int y = 1; y < 11; y++)
	{
		for (int x = 1; x < 11; x++)
		{
			if (grid1->grid[y][x]->state == Node::base && !grid1->grid[y][x]->hasShip)
			{
				gridGen[index] = '0';
			}
			else if (grid1->grid[y][x]->state == Node::hit)
			{
				gridGen[index] = 'X';
			}
			else if (grid1->grid[y][x]->state == Node::miss)
			{
				gridGen[index] = 'M';
			}
			else if (grid1->grid[y][x]->state == Node::base && grid1->grid[y][x]->hasShip && grid1->grid[y][x]->carrier)
			{
				gridGen[index] = '5';
			}
			else if (grid1->grid[y][x]->state == Node::base && grid1->grid[y][x]->hasShip && grid1->grid[y][x]->cruiser)
			{
				gridGen[index] = '4';
			}
			else if (grid1->grid[y][x]->state == Node::base && grid1->grid[y][x]->hasShip && grid1->grid[y][x]->atb)
			{
				gridGen[index] = '3';
			}
			else if (grid1->grid[y][x]->state == Node::base && grid1->grid[y][x]->hasShip && grid1->grid[y][x]->submarine)
			{
				gridGen[index] = '2';
			}
			else if (grid1->grid[y][x]->state == Node::base && grid1->grid[y][x]->hasShip && grid1->grid[y][x]->torpedo)
			{
				gridGen[index] = '1';
			}
			index++;
		}
		gridGen[index] = '/';
		index++;
	}
	for (int y = 1; y < 11; y++)
	{
		for (int x = 1; x < 11; x++)
		{
			if (grid2->grid[y][x]->state == Node::base && !grid2->grid[y][x]->hasShip)
			{
				gridGen[index] = '0';
			}
			else if (grid2->grid[y][x]->state == Node::hit)
			{
				gridGen[index] = 'X';
			}
			else if (grid2->grid[y][x]->state == Node::miss)
			{
				gridGen[index] = 'M';
			}
			else if (grid2->grid[y][x]->state == Node::base && grid2->grid[y][x]->hasShip && grid2->grid[y][x]->carrier)
			{
				gridGen[index] = '5';
			}
			else if (grid2->grid[y][x]->state == Node::base && grid2->grid[y][x]->hasShip && grid2->grid[y][x]->cruiser)
			{
				gridGen[index] = '4';
			}
			else if (grid2->grid[y][x]->state == Node::base && grid2->grid[y][x]->hasShip && grid2->grid[y][x]->atb)
			{
				gridGen[index] = '3';
			}
			else if (grid2->grid[y][x]->state == Node::base && grid2->grid[y][x]->hasShip && grid2->grid[y][x]->submarine)
			{
				gridGen[index] = '2';
			}
			else if (grid2->grid[y][x]->state == Node::base && grid2->grid[y][x]->hasShip && grid2->grid[y][x]->torpedo)
			{
				gridGen[index] = '1';
			}
			index++;
		}
		gridGen[index] = '/';
		index++;
	}
	std::cout << gridGen;
}
