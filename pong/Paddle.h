#pragma once
#include <SFML/Graphics.hpp>
class Paddle
{
	public:
		Paddle(int x, int y);
		~Paddle();

		sf::RectangleShape getSprite();

	private:
		sf::RectangleShape sprite;
		int x;
		int y;
		const float DEFAULT_RECT_HEIGHT = 100.f;
		const float DEFAULT_RECT_WIDTH = DEFAULT_RECT_HEIGHT/2;

};

