#pragma once

class Grid
{
public:
	Grid();
	~Grid();
	void CreateGrid();

	std::vector<Node*> grid;
	int shipToShoot;
};

