#include "framework.h"

Grid::Grid(sf::Vector2f pos)
{
	this->pos = pos;

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

	if (!font.loadFromFile("arial.ttf"))
	{
		throw;
	}
	
	font.loadFromFile("arial.ttf");
	// select the font
	text.setFont(font); // font is a sf::Font

	// set the character size
	text.setCharacterSize(24); // in pixels, not points!

	// set the color
	text.setFillColor(sf::Color::Black);
}

Grid::~Grid() 
{

}

void Grid::CreateGrid()
{
	shipToShoot = 17;
	for (int i = 0; i < 10; i++) 
	{
		char c = 'A' + i;
		for (int j = 0; j < 10; j++)
		{
			Node* node = new Node();
			std::string s = std::string(1, c) + std::to_string(j+1);
			node->CreateNode(i, j+1, s);
			grid[j+1][i+1] = node;
		}
	}
}

void Grid::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			gridDraw.setPosition(sf::Vector2f((float)j * 60.f, (float)i * 60.f) + pos);
			window.draw(gridDraw);

			//text.setString(grid[j + 1][i + 1]->nodeName);
			//text.setPosition(sf::Vector2f((float)j * 60.f, (float)i * 60.f) + pos);
			//window.draw(text);

			if (grid[j+1][i+1]->hasShip)
			{
				ship.setPosition(sf::Vector2f((float)j * 60.f, (float)i * 60.f) + pos);
				window.draw(ship);
				if (grid[j+ 1][i + 1]->state == Node::hit)
				{
					shipHit.setPosition(sf::Vector2f((float)j * 60.f, (float)i * 60.f) + pos);
					window.draw(shipHit);
				}
			}
			else if (grid[j + 1][i + 1]->state == Node::miss)
			{
				hit.setPosition(sf::Vector2f((float)j * 60.f, (float)i * 60.f) + pos);
				window.draw(hit);
			}
		}
	}
}

bool Grid::Click(sf::Vector2i clickpos)
{
	sf::Vector2i rClickPos = clickpos - sf::Vector2i((int)pos.x, (int)pos.y);
	rClickPos.x = (int)(floor((float)rClickPos.x / 60.f));
	rClickPos.y = (int)(floor((float)rClickPos.y / 60.f));



	return false;
}