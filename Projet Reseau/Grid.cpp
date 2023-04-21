#include "framework.h"

Grid::Grid() 
{
	grid;
	shipToShoot = 0;
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
			grid.push_back(node);
		}
	}
}
