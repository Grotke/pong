#include "Wall.h"
#include "Config.h"
#include <SFML/Graphics.hpp>


Wall::Wall(int x, int y):x(x), y(y)
{
	sprite = sf::RectangleShape(sf::Vector2f(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT / 20));
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
