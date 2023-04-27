#pragma once
class Affichage
{
private:
	sf::CircleShape hit;
	sf::CircleShape shipHit;
	sf::RectangleShape ship;

	sf::Vector2f pos;
public:
	Affichage();
	void Draw(sf::RenderWindow& window);
	void ReloadGrid();
	sf::RectangleShape gridDraw;
	std::string gridGen;
	std::vector<Grid*> grids;
};

