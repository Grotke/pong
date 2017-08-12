#pragma once
#include "Collider.h"
#include <SFML/Graphics.hpp>

class BoxCollider :
	public Collider
{
public:
	BoxCollider(sf::RectangleShape& sprite);
	virtual ~BoxCollider();

	virtual bool collidesWith(const BoxCollider& other) const override;
	virtual bool collidesWith(const CircleCollider& other) const override;
	virtual sf::Vector2f& getMinXAndY() const;
	virtual sf::Vector2f& getMaxXAndY() const;
	virtual sf::Vector2f& getMagXAndY() const;

private:
	sf::RectangleShape& sprite;
	
};

