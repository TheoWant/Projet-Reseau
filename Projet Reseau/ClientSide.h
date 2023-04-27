#pragma once
class ClientSide
{
public:
	sf::RectangleShape shipPart;
	std::string XYDown;
	void drawShip(int size, sf::Vector2f pos, bool downFaced, sf::RenderWindow& window);
	void LaunchThreads();
	void MainThread();
};

