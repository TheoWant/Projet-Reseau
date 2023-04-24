#include "Server.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 2 || argc > 2) {
		std::cout << "./server [port]" << std::endl;
		return 84;
	}
    unsigned short port = std::stoi(argv[1]);

	Server server(port);

    return 0;
}