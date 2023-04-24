#include "framework.h"

Ship::Ship(int size, sf::Vector2i& pos, bool downFaced)
{
	this->size = size;
	this->pos = pos;
	this->downFaced = downFaced;
}


Ship::~Ship()
{
}