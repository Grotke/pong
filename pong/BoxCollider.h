#pragma once
#include "Collider.h"
#include <SFML/Graphics.hpp>
#include <string>

class BoxCollider :
	public Collider
{
public:
	BoxCollider(sf::RectangleShape& sprite, std::string type);
	virtual ~BoxCollider();

	virtual float collidesWith(const BoxCollider& other) const override;
	virtual Contact collidesWith(const CircleCollider& other) const override;
	virtual sf::Vector2f& getMinXAndY() const;
	virtual sf::Vector2f& getMaxXAndY() const;
	virtual sf::Vector2f& getMagXAndY() const;
	float getHalfLengthY() const;
	float getHalfLengthX() const;
	float getCenterX() const;
	float getCenterY() const;
	const std::string getType() const;


private:
	sf::RectangleShape& sprite;
	int lastAxisOfReflection;
	std::string type;
	
};

