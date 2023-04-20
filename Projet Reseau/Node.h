#pragma once




class Node
{
public:
	Node();
	~Node();
	void CreateNode(int x, int y);

	int x_cord;
	int y_cord;

	enum State
	{
		miss,
		hit,
		base,
	};

	State state;

	bool hasShip;
	std::string name;
};

