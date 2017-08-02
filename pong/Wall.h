#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Wall:
	public GameObject
{
public:
	Wall(int x, int y);
	virtual ~Wall();

	sf::RectangleShape getSprite();


private:
	int x;
	int y;
	sf::RectangleShape sprite;
};

