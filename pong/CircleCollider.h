#pragma once
#include "Collider.h"
#include <SFML/Graphics.hpp>
class CircleCollider :
	public Collider
{
public:
	CircleCollider(sf::CircleShape& sprite);
	virtual ~CircleCollider();

	virtual bool collidesWith(const BoxCollider& other) const override;
	virtual bool collidesWith(const CircleCollider& other) const override;
	virtual sf::Vector2f& getMinXAndY() const;
	virtual sf::Vector2f& getMaxXAndY() const;
	virtual sf::Vector2f& getMagXAndY() const;

private:
	sf::CircleShape& sprite;
};

