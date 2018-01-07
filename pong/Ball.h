#pragma once

#include <SFML/Graphics.hpp>

#include "GameObject.h"

/*Attaches components to the Ball.
Initializes ball speed and direction to 
pass to the Movement Component.*/
class Ball: 
	public GameObject
{
public:
	Ball(float x, float y, float radius, float topSpeed);
	virtual ~Ball();

	sf::Vector2f getRandomDirection() const;
	float getRandomSpeed() const;
	void reset();

private:
	float radius;
	float x;
	float y;
};

