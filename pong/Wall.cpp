#include "Wall.h"
#include "Config.h"
#include <SFML/Graphics.hpp>


Wall::Wall(int x, int y):x(x), y(y)
{
	float width = Config::SCREEN_WIDTH;
	float height = Config::SCREEN_HEIGHT;
	sprite = sf::RectangleShape(sf::Vector2f(width, height / 20));
	sprite.setOrigin(width / 2, height / 40);
	sprite.setFillColor(sf::Color::White);
	sprite.setPosition(x, y);

}


Wall::~Wall()
{
}

sf::RectangleShape Wall::getSprite()
{
	return sprite;
}
