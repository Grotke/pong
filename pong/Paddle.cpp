#include "Paddle.h"
#include <SFML/Graphics.hpp>



Paddle::Paddle(int x, int y)
	: x(x), y(y)
{
	sprite = sf::RectangleShape(sf::Vector2f(DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT));
	sprite.setFillColor(sf::Color::White);
	sprite.setPosition(x, y);
}


Paddle::~Paddle()
{
}

sf::RectangleShape Paddle::getSprite() {
	return sprite;
}
