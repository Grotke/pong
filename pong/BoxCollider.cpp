#include "BoxCollider.h"
#include "CircleCollider.h"
#include <cmath>
#include <iostream>



BoxCollider::BoxCollider(sf::RectangleShape& sprite, std::string type)
	:sprite(sprite), type(type)
{
}


BoxCollider::~BoxCollider()
{
}

float BoxCollider::collidesWith(const BoxCollider& other) const
{
	float lengthBothX = other.getHalfLengthX() + getHalfLengthX();
	float lengthBothY = other.getHalfLengthY() + getHalfLengthY();
	float centerDistanceX = abs(other.getCenterX() - getCenterX());
	float centerDistanceY = abs(other.getCenterY() - getCenterY());
	float overlapX = lengthBothX - centerDistanceX;
	float overlapY = lengthBothY - centerDistanceY;

	if (overlapX < 0 || overlapY < 0)
	{
		return 0;
	}
	else
	{
		return std::min(overlapX, overlapY);
	}
}

Collider::Contact BoxCollider::collidesWith(const CircleCollider& other) const
{
	float lengthBothX = other.getHalfLengthX() + getHalfLengthX();
	float lengthBothY = other.getHalfLengthY() + getHalfLengthY();
	float centerDistanceX = abs(other.getCenterX() - getCenterX());
	float centerDistanceY = abs(other.getCenterY() - getCenterY());
	float overlapX = lengthBothX - centerDistanceX;
	float overlapY = lengthBothY - centerDistanceY;

	if (overlapX < 0 || overlapY < 0)
	{
		return Contact(0, 0, type);
	}
	else
	{
		if (overlapX < overlapY)
		{
			return Contact(1, overlapX, type);
		}
		else
		{
			return Contact(0, overlapY, type);
		}
	}
}

sf::Vector2f& BoxCollider::getMinXAndY() const
{
	sf::Vector2f pos(sprite.getPosition());
	return sf::Vector2f(pos.x - sprite.getSize().x/2, pos.y - sprite.getSize().y/2);
}

sf::Vector2f& BoxCollider::getMaxXAndY() const
{
	sf::Vector2f pos(sprite.getPosition());
	return sf::Vector2f(pos.x + sprite.getSize().x/2, pos.y + sprite.getSize().y/2);
}

sf::Vector2f& BoxCollider::getMagXAndY() const
{
	return sf::Vector2f(sprite.getSize());
}

float BoxCollider::getCenterX() const
{
	return sprite.getPosition().x;
}

float BoxCollider::getCenterY() const
{
	return sprite.getPosition().y;
}

float BoxCollider::getHalfLengthX() const
{
	return sprite.getSize().x/2;
}

float BoxCollider::getHalfLengthY() const
{
	return sprite.getSize().y/2;
}

const std::string BoxCollider::getType() const
{
	return type;
}

