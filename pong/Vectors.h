#pragma once
#include <SFML/Graphics.hpp>
class Vectors
{
public:
	Vectors();
	~Vectors();

	static sf::Vector2f normalize(const sf::Vector2f& input);
};

