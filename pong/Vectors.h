#pragma once

#include <SFML/Graphics.hpp>

/*These are some helper vector methods 
to do basic things SFML vectors can't do.*/
class Vectors
{
public:
	Vectors();
	~Vectors();

	static sf::Vector2f normalize(const sf::Vector2f& input);
	static float magnitude(const sf::Vector2f& input);
	static float dot(const sf::Vector2f& a, const sf::Vector2f& b);
};

