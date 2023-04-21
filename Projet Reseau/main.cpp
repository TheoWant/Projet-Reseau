#include "framework.h"

using namespace std;

bool game = true;

int main()
{
    Player* player1 = new Player();
    Player* player2 = new Player();

    Grid* grid = new Grid();
    grid->CreateGrid();

    for (int n = 0; n < grid->grid.size(); n++)
    {
        cout << grid->grid[n]->nodeName;
        cout << " ";
        if((n+1)%10 == 0)
            cout << "\n";
    }
    
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
