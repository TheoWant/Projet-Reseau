#pragma once

class Grid
{
private:
	sf::CircleShape hit;
	sf::CircleShape shipHit;
	sf::RectangleShape ship;
	sf::RectangleShape gridDraw;

	sf::Vector2f pos;
	sf::Font font;
	sf::Text text;

public:
	Grid(sf::Vector2f pos);
	~Grid();
	void CreateGrid();
	void Draw(sf::RenderWindow& window);
	bool Click(sf::Vector2i clickpos);

	Node* grid[10][10];
	int shipToShoot;
};

