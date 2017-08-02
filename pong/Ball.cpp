#include "Ball.h"
#include "Vectors.h"

#include <SFML/Graphics.hpp>

Ball::Ball(int x, int y):x(x), y(y)
{
	sprite = sf::CircleShape(25.f);
	sprite.setPosition(x, y);
	sprite.setFillColor(sf::Color::White);
	speedInPixelsPerSec = chooseRandomSpeed();
	direction = chooseRandomDirection();
}


Ball::~Ball()
{
}

void Ball::reset()
{
	sprite.setPosition(x, y);
	speedInPixelsPerSec = chooseRandomSpeed();
	direction = chooseRandomDirection();
}

sf::CircleShape Ball::getSprite()
{
	return sprite;
}

sf::Vector2f Ball::chooseRandomDirection()
{
	float randomX = static_cast<float> ((rand() % 200) - 100) / 100.f;
	float randomY = static_cast<float> ((rand() % 200) - 100 ) / 100.f;
	return Vectors::normalize(sf::Vector2f(randomX, randomY));
}

int Ball::chooseRandomSpeed()
{
	return rand() % 400 + 100;
}

void Ball::update(float secondsPassed)
{
	sprite.move(direction * (speedInPixelsPerSec * secondsPassed));
}

bool Ball::outOfBounds(const sf::Vector2u& screenSize)
{
	sf::Vector2f pos = sprite.getPosition();
	if (pos.x > screenSize.x || pos.y > screenSize.y || pos.y < 0 || pos.x < 0)
	{
		return true;
	}
	return false;
}
