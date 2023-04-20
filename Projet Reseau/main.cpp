#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

bool game = true;

int main()
{
    Player* player1 = new Player();
    Player* player2 = new Player();

    cout << "Entrez le nom du joueur 1: " << endl;
    fgets(player1->playerName, 30, stdin);
    player1->playerName[strcspn((player1->playerName), "\n")] = '\0';

    cout << "\nEntrez le nom du joueur 2: " << endl;
    fgets(player2->playerName, 30, stdin);
    player2->playerName[strcspn((player2->playerName), "\n")] = '\0';

    cout << "\n" << player1->playerName << " est le joueur 1 et " << player2->playerName << " est le joueur 2. \n" << endl;
    while (game == true) {

    }
    return 0;
}
