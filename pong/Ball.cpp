#include "Ball.h"

#include <SFML/Graphics.hpp>

Ball::Ball(int x, int y):x(x), y(y)
{
	sprite = sf::CircleShape(25.f);
	sprite.setPosition(x, y);
	sprite.setFillColor(sf::Color::White);
}


Ball::~Ball()
{
}

sf::CircleShape Ball::getSprite()
{
	return sprite;
}
