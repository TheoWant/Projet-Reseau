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
	shipToShoot = 17;
}

Grid::~Grid()
{

}

void Grid::CreateGrid()
{
	for (int col = 0; col < 10; col++)
	{
		char c = 'A' + col;
		for (int row = 0; row < 10; row++)
		{
			Node* node = new Node();
			std::string s = std::string(1, c) + std::to_string(row + 1);
			node->CreateNode(pos.x + (60 * row), pos.y + (60 * (col)), s);
			grid[row][col] = node;
		}
	}
}

void Grid::Draw(sf::RenderWindow& window)
{
	for (int col = 0; col < 10; col++)
	{
		for (int row = 0; row < 10; row++)
		{
			gridDraw.setPosition(sf::Vector2f((float)row * 60.f, (float)col * 60.f) + pos);
			window.draw(gridDraw);

			//text.setString(grid[j + 1][i + 1]->nodeName);
			//text.setPosition(sf::Vector2f((float)j * 60.f, (float)i * 60.f) + pos);
			//window.draw(text);

			if (grid[row][col]->hasShip)
			{
				ship.setPosition(sf::Vector2f((float)row * 60.f, (float)col * 60.f) + pos);
				window.draw(ship);
				if (grid[row][col]->state == Node::hit)
				{
					shipHit.setPosition(sf::Vector2f((float)row * 60.f, (float)col * 60.f) + pos);
					window.draw(shipHit);
				}
			}
			else if (grid[row][col]->state == Node::miss)
			{
				hit.setPosition(sf::Vector2f((float)row * 60.f, (float)col * 60.f) + pos);
				window.draw(hit);
			}
		}
	}
}

Node* Grid::CheckOnGrid(int xpos, int ypos)
{
	for (int col = 0; col < 10; col++)
	{
		for (int row = 0; row < 10; row++)
		{
			if (grid[row][col]->x_cord == xpos && grid[row][col]->y_cord == ypos)
			{
				return grid[row][col];
			}
		}
	}
	return nullptr;
}