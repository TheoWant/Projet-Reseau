#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "framework.h"

#define WM_SOCKET WM_USER + 1

Server::Server()
{
    players.clear();
    players.resize(2);
}

extern "C" LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

DWORD WINAPI Server::ServerThread(LPVOID lpParam) {
    SOCKET clientSocket;
    SOCKADDR_IN clientSocketInfo;

    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = NULL;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
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

    unsigned short port = 25565;

    Server* server = new Server();

    GameManager* gameManager = new GameManager();

    Player* player1 = new Player();
    Player* player2 = new Player();

    Grid* gridPlayer1 = new Grid();
    Grid* gridPlayer2 = new Grid();

    player1->playerTurn = true;

    gridPlayer1->CreateGrid();
    gridPlayer2->CreateGrid();

    gameManager->grids.push_back(gridPlayer1);
    gameManager->grids.push_back(gridPlayer2);

    int i = 0;

    server->listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server->listenSocket == INVALID_SOCKET)
    {
        std::cerr << "Error at listenSocket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }

    server->serverSocketInfo.sin_family = AF_INET;
    server->serverSocketInfo.sin_addr.s_addr = INADDR_ANY;
    server->serverSocketInfo.sin_port = htons(port);

    i = bind(server->listenSocket, (SOCKADDR*)&server->serverSocketInfo, sizeof(serverSocketInfo));
    if (i == SOCKET_ERROR)
    {
        std::cerr << "bind function failed with error: " << WSAGetLastError() << std::endl;
        i = closesocket(server->listenSocket);
        if (i == SOCKET_ERROR)
            std::cerr << "closesocket function failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }

    if (listen(server->listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cerr << "listen function failed with error: " << WSAGetLastError() << std::endl;
    }

    std::cout << "\033[30m\033[42mServer started.\033[0m" << std::endl;

    WSAAsyncSelect(server->listenSocket, hwnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE | FD_READ );

    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)server);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)gameManager);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)player1);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)player2);

    MSG msg;

    while (GetMessage(&msg, hwnd, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    //PostMessage();
    return 0;
}

LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Server* server = (Server*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    GameManager* gameManager = (GameManager*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    Player* player1 = (Player*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    Player* player2 = (Player*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    Grid* gridPlayer1 = (Grid*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    Grid* gridPlayer2 = (Grid*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

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
            case FD_ACCEPT:
                // Accept an incoming connection
                Accept = accept(wParam, NULL, NULL);
                // Prepare accepted socket for read, write, and close notification
                WSAAsyncSelect(Accept, hwnd, WM_SOCKET, FD_READ | FD_CLOSE);
                std::cout << "Client connected !" << std::endl;
                server->players.emplace_back((SOCKET)wParam);
                break;

            case FD_READ:
            {
                // Receive data from the socket in wParam
                char buffer[1024];
                int bytesReceived = recv(wParam, buffer, sizeof(buffer), 0);
                std::string receivedMessage(buffer, bytesReceived);
                std::cout << "Message recu du client : " << receivedMessage << std::endl;

                std::string tmpString;
                std::vector<std::string> segList;
                char separator = '/';
                for (int i = 0; i < receivedMessage.size(); i++) {
                    if (buffer[i] != separator)
                    {
                        tmpString += buffer[i];
                    }
                    else
                    {
                        segList.push_back(tmpString);
                        tmpString.clear();
                    }
                }

                std::string toSend;

                int shipPlayer1 = 0;
                int shipPlayer2 = 0;

                bool downFaced = false;

                if (segList[2] == "1")
                {
                    downFaced = true;
                }
                else
                {
                    downFaced = false;
                }

                if (server->players[0] == (SOCKET)wParam && player1->playerTurn)
                {
                    Node* node = gridPlayer1->CheckOnGrid(std::stoi(segList[0]), std::stoi(segList[1]));
                    switch (gameManager->state)
                    {
                    case GameManager::shipPlacement:
                        if (node != nullptr)
                        {
                            //Check si la case a un bateau
                            if (!node->hasShip)
                            {
                                bool canBePlaced = true;
                                for (int i = 0; i < gameManager->shipsToPlace[shipPlayer1]->size; i++)
                                {
                                    if (downFaced)
                                    {
                                        Node* nodeToCheck = gridPlayer1->CheckOnGrid(node->x_cord, node->y_cord + i * 60);
                                        if (nodeToCheck == nullptr || nodeToCheck->hasShip)
                                        {
                                            canBePlaced = false;
                                        }
                                    }
                                    else
                                    {
                                        Node* nodeToCheck = gridPlayer1->CheckOnGrid(node->x_cord + i * 60, node->y_cord);
                                        if (nodeToCheck == nullptr || nodeToCheck->hasShip)
                                        {
                                            canBePlaced = false;
                                        }
                                    }
                                }
                                if (canBePlaced)
                                {
                                    for (int i = 0; i < gameManager->shipsToPlace[shipPlayer1]->size; i++)
                                    {
                                        if (downFaced)
                                        {
                                            Node* nodeToCheck = gridPlayer1->CheckOnGrid(node->x_cord, node->y_cord + i * 60);
                                            if (nodeToCheck != nullptr || !nodeToCheck->hasShip)
                                            {
                                                nodeToCheck->hasShip = true;
                                                switch (shipPlayer1)
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
                                            Node* nodeToCheck = gridPlayer1->CheckOnGrid(node->x_cord + i * 60, node->y_cord);
                                            if (nodeToCheck != nullptr || !nodeToCheck->hasShip)
                                            {
                                                nodeToCheck->hasShip = true;
                                                switch (shipPlayer1)
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
                                        shipPlayer1++;
                                        player1->playerTurn = false;
                                        player2->playerTurn = true;
                                    }
                                }
                            }
                        }
                        break;
                    case GameManager::shipShooting:
                    {
                        Node* node = gridPlayer2->CheckOnGrid(std::stoi(segList[0]), std::stoi(segList[1]));
                        if (node != nullptr && node->state == Node::base)
                        {
                            //Check si la case a un bateau
                            if (node->hasShip)
                            {
                                node->state = Node::hit;
                                gridPlayer2->shipToShoot -= 1;
                            }
                            else
                            {
                                node->state = Node::miss;
                            }
                            //Switch player turn

                            if (gridPlayer2->shipToShoot == 0)
                            {
                                gameManager->state = GameManager::endGame;
                            }

                            player1->playerTurn = false;
                            player2->playerTurn = true;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                    gameManager->SaveGrid(gridPlayer1,gridPlayer2);
                }
                else if (server->players[1] == (SOCKET)wParam && player2->playerTurn)
                {
                    Node* node = gridPlayer2->CheckOnGrid(std::stoi(segList[0]), std::stoi(segList[1]));
                    switch (gameManager->state)
                    {
                    case GameManager::shipPlacement:
                        if (node != nullptr)
                        {
                            //Check si la case a un bateau
                            if (!node->hasShip)
                            {
                                bool canBePlaced = true;
                                for (int i = 0; i < gameManager->shipsToPlace[shipPlayer2]->size; i++)
                                {
                                    if (downFaced)
                                    {
                                        Node* nodeToCheck = gridPlayer2->CheckOnGrid(node->x_cord, node->y_cord + i * 60);
                                        if (nodeToCheck == nullptr || nodeToCheck->hasShip)
                                        {
                                            canBePlaced = false;
                                        }
                                    }
                                    else
                                    {
                                        Node* nodeToCheck = gridPlayer2->CheckOnGrid(node->x_cord + i * 60, node->y_cord);
                                        if (nodeToCheck == nullptr || nodeToCheck->hasShip)
                                        {
                                            canBePlaced = false;
                                        }
                                    }
                                }
                                if (canBePlaced)
                                {
                                    for (int i = 0; i < gameManager->shipsToPlace[shipPlayer2]->size; i++)
                                    {
                                        if (downFaced)
                                        {
                                            Node* nodeToCheck = gridPlayer2->CheckOnGrid(node->x_cord, node->y_cord + i * 60);
                                            if (nodeToCheck != nullptr || !nodeToCheck->hasShip)
                                            {
                                                nodeToCheck->hasShip = true;
                                                switch (shipPlayer2)
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
                                            Node* nodeToCheck = gridPlayer2->CheckOnGrid(node->x_cord + i * 60, node->y_cord);
                                            if (nodeToCheck != nullptr || !nodeToCheck->hasShip)
                                            {
                                                nodeToCheck->hasShip = true;
                                                switch (shipPlayer2)
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
                                        shipPlayer2++;
                                        player2->playerTurn = false;
                                        player1->playerTurn = true;
                                    }
                                }
                            }
                        }
                        break;
                    case GameManager::shipShooting:
                    {
                        Node* node = gridPlayer1->CheckOnGrid(std::stoi(segList[0]), std::stoi(segList[1]));
                        if (node != nullptr && node->state == Node::base)
                        {
                            //Check si la case a un bateau
                            if (node->hasShip)
                            {
                                node->state = Node::hit;
                                gridPlayer1->shipToShoot -= 1;
                            }
                            else
                            {
                                node->state = Node::miss;
                            }
                            //Switch player turn

                            if (gridPlayer1->shipToShoot == 0)
                            {
                                gameManager->state = GameManager::endGame;
                            }

                            player2->playerTurn = false;
                            player1->playerTurn = true;
                        }
                        break;
                    }
                    default:
                        break;
                    }
                    gameManager->SaveGrid(gridPlayer2, gridPlayer1);
                }
                
                // Send la string
                send((SOCKET)wParam, toSend.c_str(), toSend.size(), 0);
                break;
            }

            case FD_CLOSE:
                // The connection is now closed
                closesocket((SOCKET)wParam);
                break;
        }
        break;
    }
    return DefWindowProc(hwnd,uMsg,wParam,lParam);
}