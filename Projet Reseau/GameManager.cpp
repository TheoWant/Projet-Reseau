#include "framework.h"

GameManager::GameManager()
{
	sf::Vector2i pos;
	Ship* Carrier = new Ship(5,pos , false);
	Ship* Cruiser = new Ship(4,pos , false);
	Ship* ATB = new Ship(3,pos , false);
	Ship* Submarine = new Ship(3,pos , false);
	Ship* TorpedoBoat = new Ship(2,pos , false);
	shipsToPlace.push_back(Carrier);
	shipsToPlace.push_back(Cruiser);
	shipsToPlace.push_back(ATB);
	shipsToPlace.push_back(Submarine);
	shipsToPlace.push_back(TorpedoBoat);
}
