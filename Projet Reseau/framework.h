#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

class Node;
class Grid;

#include "../Server/Node.h"
#include "../Server/Grid.h"
#include "Affichage.h"