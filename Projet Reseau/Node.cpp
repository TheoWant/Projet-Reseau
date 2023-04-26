#include "framework.h"

Node::Node()
{
	x_cord = 0;
	y_cord = 0;

	state = base;

	hasShip = false;
	carrier = false;
	cruiser = false;
	atb = false;
	submarine = false;
	torpedo = false;

	nodeName = "Patrice Evra (petite blague vous fachez pas monsieur Seccia)";
}

Node::~Node()
{

}

void Node::CreateNode(int x, int y, std::string name)
{
	x_cord = x;
	y_cord = y;
	nodeName = name;
}