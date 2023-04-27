#include "framework.h"

Affichage::Affichage()
{
	hit.setRadius(6.f);
	hit.setFillColor(sf::Color::Black);
	hit.setOrigin(-12.f, -12.f);

	shipHit.setRadius(12.f);
	shipHit.setFillColor(sf::Color::Red);
	shipHit.setOrigin(-9.f, -9.f);

	ship.setFillColor(sf::Color(128, 128, 128));
	ship.setSize(sf::Vector2f(60.f, 60.f));

	gridDraw.setOutlineColor(sf::Color::Black);
	gridDraw.setOutlineThickness(1.f);
	gridDraw.setSize(sf::Vector2f(60.f, 60.f));
}

void Affichage::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < grids.size(); i++)
	{
		for (int col = 0; col < 10; col++)
		{
			for (int row = 0; row < 10; row++)
			{
				gridDraw.setPosition(sf::Vector2f((float)row * 60.f, (float)col * 60.f) + pos);
				window.draw(gridDraw);

				if (grids[i]->grid[row][col]->hasShip)
				{
					ship.setPosition(sf::Vector2f((float)row * 60.f, (float)col * 60.f) + pos);
					window.draw(ship);
					if (grids[i]->grid[row][col]->state == Node::hit)
					{
						shipHit.setPosition(sf::Vector2f((float)row * 60.f, (float)col * 60.f) + pos);
						window.draw(shipHit);
					}
				}
				else if (grids[i]->grid[row][col]->state == Node::miss)
				{
					hit.setPosition(sf::Vector2f((float)row * 60.f, (float)col * 60.f) + pos);
					window.draw(hit);
				}
			}
		}
	}
}

void Affichage::ReloadGrid()
{
	int indexOfGrid = 0;
	for (int i = 0; i < gridGen.size(); i++)
	{
		int x = i % 11;
		int y = (int)floor(i / 11) - indexOfGrid * 11;
		if (i == gridGen.size() / 2)
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