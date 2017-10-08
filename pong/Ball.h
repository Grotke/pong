#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
class Ball: 
	public GameObject
{
public:
	Ball(float x, float y, float radius, float topSpeed);
	virtual ~Ball();

	sf::Vector2f chooseRandomDirection();
	float chooseRandomSpeed();
	void reset();
	void incrementScore(int player) const;

private:
	float radius = 25.f;
	float x;
	float y;
};

