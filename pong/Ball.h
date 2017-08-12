#pragma once
#include "GameObject.h"
#include "Collision.h"
#include <SFML/Graphics.hpp>
class Ball: 
	public GameObject
{
public:
	Ball(int x, int y);
	virtual ~Ball();

	sf::CircleShape& getSprite();
	sf::Vector2f chooseRandomDirection();
	int chooseRandomSpeed();
	void update(float secondsPassed, const Collision& c, const CircleCollider& b);
	void reset();
	bool outOfBounds(const sf::Vector2u& screenSize);
	void incrementScore(int player) const;

private:
	sf::CircleShape sprite;
	float speedInPixelsPerSec;
	sf::Vector2f direction;
	float radius = 25.f;
	int x;
	int y;
};

