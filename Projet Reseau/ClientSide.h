#pragma once
class ClientSide
{
public:
	static HWND hwnd;
	sf::RectangleShape shipPart;
	std::string XYDown;
	void drawShip(int size, sf::Vector2f pos, bool downFaced, sf::RenderWindow& window);
	void MainThread();
	static DWORD WINAPI ClientToServerThread(LPVOID lpParam);
};

