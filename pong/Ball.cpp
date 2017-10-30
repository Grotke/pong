#include "Ball.h"
#include "Vectors.h"
#include "ScoreKeeper.h"
#include "SoundManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ComponentManager.h"
#include <iostream>
Ball::Ball(float x, float y, float radius, float topSpeed): GameObject("Ball")
{
	float speedInPixelsPerSec = chooseRandomSpeed();
	sf::Vector2f initDirection = chooseRandomDirection();
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
	float speedInPixelsPerSec = chooseRandomSpeed();
	sf::Vector2f initDirection = chooseRandomDirection();
	ComponentManager::getTransformByParent(*this).reset();
	ComponentManager::getMovementByParent(*this).setMoveDirection(initDirection);
	ComponentManager::getMovementByParent(*this).setCurrentSpeed(speedInPixelsPerSec);
}

sf::Vector2f Ball::chooseRandomDirection()
{
	float randomX = static_cast<float> ((rand() % 200) - 100);
	float randomY = static_cast<float> ((rand() % 200) - 100);
	return Vectors::normalize(sf::Vector2f(randomX, randomY));
}

float Ball::chooseRandomSpeed()
{
	return rand() % 400 + 200;
}

void Ball::incrementScore(int player) const
{

	ScoreKeeper::incrementScore(player);
}
