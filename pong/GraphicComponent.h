#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"

/*This component attaches a graphic to an object.
It's needed for the object to be rendered.
Because sf::Shape is an abstract class and can't be instantiated, 
there's a variable for both a rectangle and a circle, 
but any object should only have one shape. 
This is set in the constructor by the isCircle parameter.*/
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

