#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
class GraphicComponent :
	public Component
{
public:
	GraphicComponent(int parentId, bool isCircle);
	virtual ~GraphicComponent();
	sf::Shape& getSprite();

private:
	sf::CircleShape circleSprite;
	sf::RectangleShape recSprite;
	sf::Color fillColor = sf::Color::White;
	bool isCircle;
};

