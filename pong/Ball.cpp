#include "Ball.h"
#include "ComponentManager.h"
#include "ScoreKeeper.h"
#include "Vectors.h"

/*The ball spawns with a random speed and a random direction.
Every respawn changes the starting speed and direction.
The ball produces audio depending on what it collides with.*/
Ball::Ball(float x, float y, float radius, float topSpeed): GameObject("Ball")
{
	float speedInPixelsPerSec = getRandomSpeed();
	sf::Vector2f initDirection = getRandomDirection();
	ComponentManager::addTransformTo(*this, sf::Vector2f(x, y), radius * 2, radius * 2);
	ComponentManager::addGraphicTo(*this, true);
	ComponentManager::addColliderTo(*this);
	ComponentManager::addMovementTo(*this, initDirection, speedInPixelsPerSec, topSpeed, true);
	ComponentManager::addAudioTo(*this);
}

Ball::~Ball()
{
}

void Ball::reset()
{
	float speedInPixelsPerSec = getRandomSpeed();
	sf::Vector2f initDirection = getRandomDirection();
	ComponentManager::getTransformByParent(*this).reset();
	ComponentManager::getMovementByParent(*this).setMoveDirection(initDirection);
	ComponentManager::getMovementByParent(*this).setCurrentSpeed(speedInPixelsPerSec);
}

sf::Vector2f Ball::getRandomDirection() const
{
	//Coords range from -100 to 100
	float randomX = static_cast<float> ((rand() % 200) - 100);
	float randomY = static_cast<float> ((rand() % 200) - 100);
	return Vectors::normalize(sf::Vector2f(randomX, randomY));
}

float Ball::getRandomSpeed() const
{
	return rand() % 400 + 200;
}
