#include "framework.h"

Grid::Grid()
{
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
			node->CreateNode((60 * row), (60 * (col)), s);
			grid[row][col] = node;
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