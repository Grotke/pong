#include <math.h>

#include "Vectors.h"

Vectors::Vectors()
{
}

Vectors::~Vectors()
{
}

sf::Vector2f Vectors::normalize(const sf::Vector2f& input)
{
	float mag = magnitude(input);

	//Make sure the vector isn't 0 to prevent divide by zero error.
	if (mag)
	{
		return sf::Vector2f(input.x / mag, input.y / mag);
	}
	return sf::Vector2f(0.f, 0.f);
}

float Vectors::dot(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return a.x * b.x + a.y * b.y;
}

float Vectors::magnitude(const sf::Vector2f& input)
{
	float magSquared = input.x * input.x + input.y * input.y;
	return sqrt(magSquared);
}
