#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"

/*This component holds the position, width and height of an object.
It can also test for out of bounds, which is used 
to determine if a ball has been scored.*/
class TransformComponent :
	public Component
{
	public:
		TransformComponent(int parentId, const sf::Vector2f& startPosition, float height, float width);
		virtual ~TransformComponent();
		void update(float secondsPassed);
		void setPosition(float x, float y);
		void setPosition(const sf::Vector2f& newPos);
		void addPosition(const sf::Vector2f& add);
		void addPosition(float x, float y);
		int isOutOfBounds(const sf::Vector2u& screenSize);
		const sf::Vector2f& getPosition() const;
		float getWidth() const;
		float getHeight() const;
		void reset();

	private:
		sf::Vector2f position;
		sf::Vector2f startPos;
		float height;
		float width;


};

