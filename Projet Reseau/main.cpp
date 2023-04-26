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
	// ========== faut ranger ca ==========

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

	connect(sock, (SOCKADDR*)&socketInfo, sizeof(socketInfo)); // connect to server
	int readCount = recv(sock, input, 1024, 0);
	if (readCount != SOCKET_ERROR) // receive data from server
	{
		input[readCount] = 0;
		cout << input << " Ce que le serveur envoie" << endl; // print data
	}

	bool shipsReady = false;
	GameManager gameManager;
	gameManager.state = GameManager::shipPlacement;

	Player player1;
	player1.playerTurn = true;

	Player player2;

	sf::RenderWindow window(sf::VideoMode(1380, 720), "Sea Battle", sf::Style::Titlebar | sf::Style::Close);
	srand(static_cast<unsigned int>(time(0)));

	shipPart.setFillColor(sf::Color(128, 128, 128, 128));
	shipPart.setSize(sf::Vector2f(60.f, 60.f));

	Grid gridPlayer1(sf::Vector2f(60, 60));
	Grid gridPlayer2(sf::Vector2f(720, 60));

	gridPlayer1.CreateGrid();
	gridPlayer2.CreateGrid();

	gameManager.SaveGrid(&gridPlayer1, &gridPlayer2);

	int size = 4;
	int sizestep = 1;
	bool downFaced = false;

	int shipPlacement = 0;

	std::string tmp = gameManager.gridSave.str();
	send(sock, tmp.c_str(), tmp.size(), 0);

	closesocket(sock); // close socket (temporaire, faut le metre autre pars)
	WSACleanup(); // close winsock

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
				//Check tour du joueur
				if (player1.playerTurn)
				{
					//Check pos souris

					if (gameManager.state == GameManager::shipPlacement)
					{
						Node* node = gridPlayer1.CheckOnGrid(x, y);
						//Si sur une case
						if (node != nullptr)
						{
							//Check si la case a un bateau
							if (!node->hasShip)
							{
								bool canBePlaced = true;
								for (int i = 0; i < gameManager.shipsToPlace[shipPlacement]->size; i++)
								{
									if (downFaced)
									{
										Node* nodeToCheck = gridPlayer1.CheckOnGrid(node->x_cord, node->y_cord + i * 60);
										if (nodeToCheck == nullptr || nodeToCheck->hasShip)
										{
											canBePlaced = false;
										}
									}
									else
									{
										Node* nodeToCheck = gridPlayer1.CheckOnGrid(node->x_cord + i * 60, node->y_cord);
										if (nodeToCheck == nullptr || nodeToCheck->hasShip)
										{
											canBePlaced = false;
										}
									}
								}
								if (canBePlaced)
								{
									for (int i = 0; i < gameManager.shipsToPlace[shipPlacement]->size; i++)
									{
										if (downFaced)
										{
											Node* nodeToCheck = gridPlayer1.CheckOnGrid(node->x_cord, node->y_cord + i * 60);
											if (nodeToCheck != nullptr || !nodeToCheck->hasShip)
											{
												nodeToCheck->hasShip = true;
												switch (shipPlacement)
												{
												case 0:
													nodeToCheck->carrier = true;
													break;
												case 1:
													nodeToCheck->cruiser = true;
													break;
												case 2:
													nodeToCheck->atb = true;
													break;
												case 3:
													nodeToCheck->submarine = true;
													break;
												case 4:
													nodeToCheck->torpedo = true;
													break;
												default:
													break;
												}
											}
										}
										else
										{
											Node* nodeToCheck = gridPlayer1.CheckOnGrid(node->x_cord + i * 60, node->y_cord);
											if (nodeToCheck != nullptr || !nodeToCheck->hasShip)
											{
												nodeToCheck->hasShip = true;
												switch (shipPlacement)
												{
												case 0:
													nodeToCheck->carrier = true;
													break;
												case 1:
													nodeToCheck->cruiser = true;
													break;
												case 2:
													nodeToCheck->atb = true;
													break;
												case 3:
													nodeToCheck->submarine = true;
													break;
												case 4:
													nodeToCheck->torpedo = true;
													break;
												default:
													break;
												}
											}
										}
									}
									//Switch player turn
									player1.playerTurn = false;
									player2.playerTurn = true;
								}
							}
						}
					}
					else if (gameManager.state == GameManager::shipShooting)
					{
						Node* node = gridPlayer2.CheckOnGrid(x, y);
						if (node != nullptr && node->state == Node::base)
						{
							//Check si la case a un bateau
							if (node->hasShip)
							{
								node->state = Node::hit;
								gridPlayer2.shipToShoot -= 1;
							}
							else
							{
								node->state = Node::miss;
							}
							//Switch player turn

							if (gridPlayer2.shipToShoot == 0)
							{
								gameManager.state = GameManager::endGame;
							}

							player1.playerTurn = false;
							player2.playerTurn = true;
						}
					}
					system("cls");
					gameManager.SaveGrid(&gridPlayer1,&gridPlayer2);
				}
				else if(player2.playerTurn)
				{
					//Check pos souris

					if (gameManager.state == GameManager::shipPlacement)
					{
						Node* node = gridPlayer2.CheckOnGrid(x, y);
						//Si sur une case
						if (node != nullptr)
						{
							//Check si la case a un bateau
							if (!node->hasShip)
							{
								bool canBePlaced = true;
								for (int i = 0; i < gameManager.shipsToPlace[shipPlacement]->size; i++)
								{
									if (downFaced)
									{
										Node* nodeToCheck = gridPlayer2.CheckOnGrid(node->x_cord, node->y_cord + i * 60);
										if (nodeToCheck == nullptr || nodeToCheck->hasShip)
										{
											canBePlaced = false;
										}
									}
									else
									{
										Node* nodeToCheck = gridPlayer2.CheckOnGrid(node->x_cord + i * 60, node->y_cord);
										if (nodeToCheck == nullptr || nodeToCheck->hasShip)
										{
											canBePlaced = false;
										}
									}
								}
								if (canBePlaced)
								{
									for (int i = 0; i < gameManager.shipsToPlace[shipPlacement]->size; i++)
									{
										if (downFaced)
										{
											Node* nodeToCheck = gridPlayer2.CheckOnGrid(node->x_cord, node->y_cord + i * 60);
											if (nodeToCheck != nullptr || !nodeToCheck->hasShip)
											{
												nodeToCheck->hasShip = true;
												switch (shipPlacement)
												{
												case 0:
													nodeToCheck->carrier = true;
													break;
												case 1:
													nodeToCheck->cruiser = true;
													break;
												case 2:
													nodeToCheck->atb = true;
													break;
												case 3:
													nodeToCheck->submarine = true;
													break;
												case 4:
													nodeToCheck->torpedo = true;
													break;
												default:
													break;
												}
											}
										}
										else
										{
											Node* nodeToCheck = gridPlayer2.CheckOnGrid(node->x_cord + i * 60, node->y_cord);
											if (nodeToCheck != nullptr || !nodeToCheck->hasShip)
											{
												nodeToCheck->hasShip = true;
												switch (shipPlacement)
												{
												case 0:
													nodeToCheck->carrier = true;
													break;
												case 1:
													nodeToCheck->cruiser = true;
													break;
												case 2:
													nodeToCheck->atb = true;
													break;
												case 3:
													nodeToCheck->submarine = true;
													break;
												case 4:
													nodeToCheck->torpedo = true;
													break;
												default:
													break;
												}
											}
										}
									}
									//Switch player turn
									player2.playerTurn = false;
									player1.playerTurn = true;
									if (shipPlacement == gameManager.shipsToPlace.size() -1)
									{
										gameManager.state = GameManager::shipShooting;
									}
									else 
									{
										shipPlacement++;
									}
								}
							}
						}
					}
					else if (gameManager.state == GameManager::shipShooting)
					{
						Node* node = gridPlayer1.CheckOnGrid(x, y);
						if (node != nullptr && node->state == Node::base)
						{
							//Check si la case a un bateau
							if (node->hasShip)
							{
								node->state = Node::hit;
								gridPlayer1.shipToShoot -= 1;
							}
							else
							{
								node->state = Node::miss;
							}
							//Switch player turn
							if (gridPlayer1.shipToShoot == 0)
							{
								gameManager.state = GameManager::endGame;
							}
							player2.playerTurn = false;
							player1.playerTurn = true;
						}
					}
					system("cls");
					gameManager.SaveGrid(&gridPlayer1, &gridPlayer2);
				}
			}
			if (event.type == sf::Event::MouseWheelMoved)
			{
				downFaced = !downFaced;
			}
		}

		window.clear(sf::Color(200, 200, 200));

		if (gameManager.state == GameManager::endGame)
		{
			if (player1.playerTurn)
			{
				gridPlayer2.gridDraw.setFillColor(sf::Color::Green);
				gridPlayer1.gridDraw.setFillColor(sf::Color::Red);
			}
			else if (player2.playerTurn)
			{
				gridPlayer1.gridDraw.setFillColor(sf::Color::Green);
				gridPlayer2.gridDraw.setFillColor(sf::Color::Red);
			}
		}

		gridPlayer1.Draw(window);
		gridPlayer2.Draw(window);

		if (gameManager.state == GameManager::shipPlacement)
		{
			drawShip(gameManager.shipsToPlace[shipPlacement]->size, sf::Vector2f(x, y), downFaced, window);
		}

		window.display();
	}

	return 0;
}
