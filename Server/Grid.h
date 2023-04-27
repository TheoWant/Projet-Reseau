#pragma once

class Grid
{
public:
	char* gridGen;
	sf::RectangleShape gridDraw;
	Grid();
	~Grid();
	void CreateGrid();
	Node* CheckOnGrid(int x, int y);

	Node* grid[10][10];
	int shipToShoot;
};

