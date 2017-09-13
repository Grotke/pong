#include "Paddle.h"
#include "BoxCollider.h"
#include <SFML/Graphics.hpp>
#include <iostream>



Paddle::Paddle(int x, int y, Controller& control)
	: x(x), y(y), controller(control)
{
	float width = DEFAULT_RECT_WIDTH;
	float height = DEFAULT_RECT_HEIGHT;
	sprite = sf::RectangleShape(sf::Vector2f(width, height));
	sprite.setOrigin(width / 2, height / 2);
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

const sf::Vector2f& Paddle::getPosition() const
{
	return sprite.getPosition();
}

sf::RectangleShape& Paddle::getSprite() 
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

int Paddle::getStartY() const
{
	return y;
}

void Paddle::update(float secondsPassed, const Collision& c, const BoxCollider& b)
{
	if (!(moveUp || moveDown))
	{
		currentSpeed = 0;
	}
	if (moveUp)
	{
		currentSpeed = calculateNewSpeed(secondsPassed);
		sprite.move(0, -secondsPassed*currentSpeed);
		auto output = c.resolve(b);
		if (output)
		{
			sprite.setFillColor(sf::Color::Green);
			sprite.move(0, output);
		}
		else
		{
			sprite.setFillColor(sf::Color::White);
		}
	}
	if (moveDown)
	{
		currentSpeed = calculateNewSpeed(secondsPassed);
		sprite.move(0, secondsPassed*currentSpeed);
		auto output = c.resolve(b);
		if (output)
		{
			sprite.setFillColor(sf::Color::Green);
			sprite.move(0, -output);

		}
		else
		{
			sprite.setFillColor(sf::Color::White);
		}
	}
}

float Paddle::calculateNewSpeed(float secondsPassed)
{
	float newSpeed = (acceleration * secondsPassed) + currentSpeed;
	if (newSpeed > speedInPixelsPerSec)
	{
		newSpeed = speedInPixelsPerSec;
	}
	return speedInPixelsPerSec;
	//return newSpeed;
}


