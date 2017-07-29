#pragma once
#include <SFML/Graphics.hpp>
class Ball
{
public:
	Ball(int x, int y);
	~Ball();

	sf::CircleShape getSprite();

private:
	sf::CircleShape sprite;
	float radius;
	int x;
	int y;
};

