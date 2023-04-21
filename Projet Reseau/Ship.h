#pragma once
class Ship
{
public:
	int size;
	sf::Vector2i pos;
	bool downFaced;

	Ship(int size, sf::Vector2i& pos, bool downFaced);
	~Ship();

};

