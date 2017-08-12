#pragma once
#include "Collider.h"
#include <SFML/Graphics.hpp>
class CircleCollider :
	public Collider
{
public:
	CircleCollider(sf::CircleShape& sprite);
	virtual ~CircleCollider();

	virtual float collidesWith(const BoxCollider& other) const override;
	virtual Contact collidesWith(const CircleCollider& other) const override;
	virtual sf::Vector2f& getMinXAndY() const;
	virtual sf::Vector2f& getMaxXAndY() const;
	virtual sf::Vector2f& getMagXAndY() const;
	float getHalfLengthY() const;
	float getHalfLengthX() const;
	float getCenterX() const;
	float getCenterY() const;

private:
	sf::CircleShape& sprite;
};

