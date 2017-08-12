#include "Vectors.h"
#include <math.h>


Vectors::Vectors()
{
}


Vectors::~Vectors()
{
}

sf::Vector2f Vectors::normalize(const sf::Vector2f& input)
{
	float magSquared = input.x * input.x + input.y * input.y;
	float mag = sqrt(magSquared);

	return sf::Vector2f(input.x / mag, input.y / mag);
}

float Vectors::dot(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return a.x * b.x + a.y * b.y;
}
