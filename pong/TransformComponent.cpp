#include "TransformComponent.h"

TransformComponent::TransformComponent(int parentId, const sf::Vector2f& startPosition, float height, float width) 
	: Component(parentId), startPos(startPosition), height(height), width(width)
{
	setPosition(startPosition);
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::reset()
{
	setPosition(startPos);
}

void TransformComponent::update(float secondsPassed)
{
}

void TransformComponent::setPosition(float x, float y)
{
	position = sf::Vector2f(x, y);
}

void TransformComponent::setPosition(const sf::Vector2f& newPos)
{
	position = newPos;
}

void TransformComponent::addPosition(const sf::Vector2f& add)
{
	position += add;
}

void TransformComponent::addPosition(float x, float y)
{
	position.x += x;
	position.y += y;
}

//Returns -1 if scored left, 1 if scored right and 0 if still in play.
int TransformComponent::isOutOfBounds(const sf::Vector2u& screenSize)
{
	if (position.x > screenSize.x || position.y > screenSize.y || position.y < 0 || position.x < 0)
	{
		if (position.x < 0)
		{
			return -1;
		}
		else if (position.x > screenSize.x)
		{
			return 1;
		}
	}
	return 0;
}

float TransformComponent::getWidth() const
{
	return width;
}

float TransformComponent::getHeight() const
{
	return height;
}

const sf::Vector2f& TransformComponent::getPosition() const
{
	return position;
}