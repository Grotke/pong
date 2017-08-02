#include "Paddle.h"
#include <SFML/Graphics.hpp>



Paddle::Paddle(int x, int y, Controller& control)
	: x(x), y(y), controller(control)
{
	sprite = sf::RectangleShape(sf::Vector2f(DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT));
	sprite.setFillColor(sf::Color::White);
	sprite.setPosition(x, y);
	controller.attachParent(this);
}


Paddle::~Paddle()
{
}

void Paddle::reset()
{
	sprite.setPosition(x, y);
}

sf::RectangleShape Paddle::getSprite() 
{
	return sprite;
}

void Paddle::enableMoveUp()
{
	moveUp = true;
}

void Paddle::enableMoveDown()
{
	moveDown = true;
}

void Paddle::disableMoveUp()
{
	moveUp = false;
}

void Paddle::disableMoveDown()
{
	moveDown = false;
}

void Paddle::update(float secondsPassed)
{
	if (moveUp)
	{
		sprite.move(0, -secondsPassed*speedInPixelsPerSec);
	}
	if (moveDown)
	{
		sprite.move(0, secondsPassed*speedInPixelsPerSec);
	}
}


