#include "framework.h"

///////#define _WINSOCK_DEPRECATED_NO_WARNINGS

using namespace std;

bool game = true;

sf::RectangleShape shipPart;


void drawShip(int size, sf::Vector2f pos, bool downFaced, sf::RenderWindow& window)
{
	for (int i = 0; i < size; i++)
	{
		if (downFaced)
		{
			shipPart.setPosition(pos.x, pos.y + i * 60);
		}
		else
		{
			shipPart.setPosition(pos.x + i * 60, pos.y);
		}
		window.draw(shipPart);
	}
}

int main()
{
	WSADATA WSAData;
	SOCKET sock;
	SOCKADDR_IN socketInfo;
	std::string s;
	char input[1024+1];

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0) {}

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	InetPton(AF_INET, L"127.0.0.1", &socketInfo.sin_addr.s_addr);
	socketInfo.sin_family = AF_INET;
	socketInfo.sin_port = htons(25565);

	Sleep(1000);

	int connection = connect(sock, (SOCKADDR*)&socketInfo, sizeof(socketInfo)); // connect to server
	if (connection != 0)
	{
		
	}

	sf::RenderWindow window(sf::VideoMode(1380, 720), "Sea Battle", sf::Style::Titlebar | sf::Style::Close);
	srand(static_cast<unsigned int>(time(0)));

	int size = 4;
	int sizestep = 1;
	bool downFaced = false;

	int shipPlacement = 0;

	//closesocket(sock); // close socket (temporaire, faut le metre autre pars)
	//WSACleanup(); // close winsock

	while (window.isOpen())
	{
		int x = sf::Mouse::getPosition(window).x - (sf::Mouse::getPosition(window).x % 60);
		int y = sf::Mouse::getPosition(window).y - (sf::Mouse::getPosition(window).y % 60);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonReleased)
			{
				// to do
				// Send une char avec la pos de la souris (x,y, bool isDownfaced(0 ou 1))
				std::string XYDown =  std::to_string(x) + "/" + std::to_string(y) + "/" + std::to_string(downFaced) + "/";
				send(sock, XYDown.c_str(), XYDown.size(), 0);
			}
			if (event.type == sf::Event::MouseWheelMoved)
			{
				downFaced = !downFaced;
			}
		}

		window.clear(sf::Color(200, 200, 200));
		window.display();
		
	}

	return 0;
}
