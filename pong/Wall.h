#pragma once
#include <SFML/Graphics.hpp>

class Wall
{
public:
	Wall(int x, int y);
	~Wall();

	sf::RectangleShape getSprite();


private:
	int x;
	int y;
	sf::RectangleShape sprite;
};

