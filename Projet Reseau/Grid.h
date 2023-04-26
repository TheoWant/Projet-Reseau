#pragma once

class Grid
{
private:
	sf::CircleShape hit;
	sf::CircleShape shipHit;
	sf::RectangleShape ship;

	sf::Vector2f pos;
	sf::Font font;
	sf::Text text;

public:
	char* gridGen;
	sf::RectangleShape gridDraw;
	Grid(sf::Vector2f pos);
	~Grid();
	void CreateGrid();
	void Draw(sf::RenderWindow& window);
	Node* CheckOnGrid(int x, int y);

	Node* grid[10][10];
	int shipToShoot;
};

