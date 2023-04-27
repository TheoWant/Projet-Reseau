#include "framework.h"

#define WM_SOCKET WM_USER + 1

using namespace std;

bool game = true;

sf::RectangleShape shipPart;

HWND hwnd;
std::string XYDown;

extern "C" LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
	sf::RenderWindow window(sf::VideoMode(1380, 720), "Sea Battle", sf::Style::Titlebar | sf::Style::Close);
	srand(static_cast<unsigned int>(time(0)));

	bool downFaced = false;

	int shipPlacement = 0;

	Affichage* affichage = new Affichage();

	Grid* gridPlayer = new Grid();
	Grid* gridEnnemy = new Grid();

	affichage->grids.push_back(gridPlayer);
	affichage->grids.push_back(gridEnnemy);

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
				XYDown = std::to_string(x) + "/" + std::to_string(y) + "/" + std::to_string(downFaced) + "/";
				PostMessage(hwnd, 1, NULL, NULL);
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

LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	SOCKET Accept;

	switch (uMsg)
	{

	case WM_SOCKET:
		// Determine whether an error occurred on the
		// socket by using the WSAGETSELECTERROR() macro
		if (WSAGETSELECTERROR(lParam))
		{
			// Display the error and close the socket
			closesocket((SOCKET)wParam);
			break;
		}
		// Determine what event occurred on the socket
		switch (WSAGETSELECTEVENT(lParam))
		{
		case FD_READ:
		{
			// Receive data from the socket in wParam
			char buffer[1024];
			int message = recv((SOCKET)wParam, buffer, sizeof(buffer), 0);
			if (message == 1)
			{
				send(Accept, XYDown.c_str(),XYDown.size(),0);
			}
			break;
		}

		case FD_CLOSE:
			// The connection is now closed
			closesocket((SOCKET)wParam);
			break;
		}
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


DWORD WINAPI ClientToServerThread(LPVOID lpParam) {
	WSADATA WSAData;
	SOCKET sock;
	SOCKADDR_IN socketInfo;
	std::string s;
	char input[1024 + 1];

	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = NULL;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window.

	HWND hWnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		NULL,       // Instance handle
		NULL        // Additional application data
	);

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0) {}

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	InetPton(AF_INET, L"127.0.0.1", &socketInfo.sin_addr.s_addr);
	socketInfo.sin_family = AF_INET;
	socketInfo.sin_port = htons(25565);

	Sleep(1000);
	int connection = connect(sock, (SOCKADDR*)&socketInfo, sizeof(socketInfo)); // connect to server

	MSG msg;

	while (GetMessage(&msg, hWnd, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


void LaunchThreads()
{
	HANDLE hThread;
	DWORD dwThreadId;
	hThread = CreateThread(NULL, 0, ClientToServerThread, NULL, 0, &dwThreadId);
}