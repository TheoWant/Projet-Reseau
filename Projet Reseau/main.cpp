#include "framework.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
///////#define _WINSOCK_DEPRECATED_NO_WARNINGS

using namespace std;

bool game = true;

sf::RectangleShape shipPart;



/*void drawShip(int size, sf::Vector2f pos, bool downFaced, sf::RenderWindow& window)
{
	for (int i = 0; i < size; i++)
	{
		if (downFaced)
		{
			shipPart.setPosition(pos.x, pos.y + i * 30);
		}
		else
		{
			shipPart.setPosition(pos.x + i * 30, pos.y);
		}
		window.draw(shipPart);
	}
}

bool placeShip(sf::Vector2i pos, int size, bool downFaced, Field& f)
{
	if (f.CheckShip(pos, size, downFaced))
	{
		f.AddShip(Ship(size, pos, downFaced));
		return true;
	}
	return false;
}*/

int main()
{
	WSADATA WSAData;
	SOCKET sock;
	SOCKADDR_IN socketInfo;
	char buffer[255];

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0) {}

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	///socketInfo.sin_addr.s_addr = InetPton("127.0.0.1");
	InetPton(AF_INET, L"127.0.0.1", &socketInfo.sin_addr.s_addr);
	socketInfo.sin_family = AF_INET;
	socketInfo.sin_port = htons(25565);
	connect(sock, (SOCKADDR*)&socketInfo, sizeof(socketInfo));
	if (recv(sock, buffer, sizeof(buffer), 0) != SOCKET_ERROR)
	{
		cout << buffer << endl;
	}
	closesocket(sock);
	WSACleanup();









	bool shipsReady = false;
	sf::RenderWindow window(sf::VideoMode(1380, 720), "Sea Battle", sf::Style::Titlebar | sf::Style::Close);
	srand(static_cast<unsigned int>(time(0)));

	shipPart.setFillColor(sf::Color(128, 128, 128, 128));
	shipPart.setSize(sf::Vector2f(60.f, 60.f));

	Grid gridPlayer(sf::Vector2f(60, 60));
	Grid gridEnemy(sf::Vector2f(720, 60));

	gridPlayer.CreateGrid();
	gridEnemy.CreateGrid();

	//f.RandomizeShips();
	//f1.RandomizeShips();


	int size = 4;
	int sizestep = 1;
	bool downFaced = false;



	while (window.isOpen())
	{
		int x = sf::Mouse::getPosition(window).x - (sf::Mouse::getPosition(window).x % 30);
		int y = sf::Mouse::getPosition(window).y - (sf::Mouse::getPosition(window).y % 30);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonReleased)
			{
				
			}
			if (event.type == sf::Event::MouseWheelMoved)
			{
				downFaced = !downFaced;
			}
		}

		//if (gridPlayer.CheckLose())
		//{
		//	gridEnemy.SetEnemyTransp(255);
		//}

		window.clear(sf::Color(200, 200, 200));

		gridPlayer.Draw(window);
		gridEnemy.Draw(window);

		//drawShip(size, sf::Vector2f(x, y), downFaced, window);

		window.display();
	}

	return 0;
}
