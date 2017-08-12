#include "CircleCollider.h"
#include "BoxCollider.h"
#include <SFML/Graphics.hpp>



CircleCollider::CircleCollider(sf::CircleShape& sprite)
	:sprite(sprite)
{
}


CircleCollider::~CircleCollider()
{
}

float CircleCollider::collidesWith(const BoxCollider& other) const
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

Collider::Contact CircleCollider::collidesWith(const CircleCollider& other) const
{
	float lengthBothX = other.getHalfLengthX() + getHalfLengthX();
	float lengthBothY = other.getHalfLengthY() + getHalfLengthY();
	float centerDistanceX = abs(other.getCenterX() - getCenterX());
	float centerDistanceY = abs(other.getCenterY() - getCenterY());
	float overlapX = lengthBothX - centerDistanceX;
	float overlapY = lengthBothY - centerDistanceY;

	if (overlapX < 0 || overlapY < 0)
	{
		return Contact(0,0);
	}
	else
	{
		return Contact(0, std::min(overlapX, overlapY));
	}
}

sf::Vector2f& CircleCollider::getMinXAndY() const
{
	sf::Vector2f pos(sprite.getPosition());
	return sf::Vector2f(pos.x - sprite.getRadius(), pos.y - sprite.getRadius());
}

sf::Vector2f& CircleCollider::getMaxXAndY() const
{
	sf::Vector2f pos(sprite.getPosition());
	return sf::Vector2f(pos.x + sprite.getRadius(), pos.y + sprite.getRadius());
}

sf::Vector2f& CircleCollider::getMagXAndY() const
{
	sf::Vector2f min(getMinXAndY());
	sf::Vector2f max(getMaxXAndY());
	return max - min;
}

float CircleCollider::getCenterX() const
{
	return sprite.getPosition().x;
}

float CircleCollider::getCenterY() const
{
	return sprite.getPosition().y;
}

float CircleCollider::getHalfLengthX() const
{
	return sprite.getRadius();
}

float CircleCollider::getHalfLengthY() const
{
	return sprite.getRadius();
}


