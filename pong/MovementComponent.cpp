#include "MovementComponent.h"
#include "ComponentManager.h"
#include "Vectors.h"



MovementComponent::MovementComponent(int parentId, const sf::Vector2f& startDir, float startSpeed, float topSpeed, bool isBouncy)
	: Component(parentId), startDirection(startDir), moveDirection(startDir), startSpeed(startSpeed), currentSpeed(startSpeed), topSpeed(topSpeed), isBouncy(isBouncy)
{
	movingTowards = false;
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::setMoveDirection(const sf::Vector2f& movePos)
{
	moveDirection = movePos;
}

void MovementComponent::setCurrentSpeed(float newSpeed)
{
	currentSpeed = newSpeed;
}

void MovementComponent::update(float secondsPassed)
{
	float moveMag = 0.f;
	if (movingTowards)
	{
		float magnitude = Vectors::magnitude(moveTowardsVec);
		sf::Vector2f moveDir = Vectors::normalize(moveTowardsVec);
		if ((secondsPassed * currentSpeed) < magnitude)
		{
			moveMag = secondsPassed * currentSpeed;
		}
		else
		{
			moveMag = magnitude;
		}
		moveDirection = moveDir;
		movingTowards = false;
	}
	else
	{
		moveMag = secondsPassed * currentSpeed;
	}
	ComponentManager::getTransformById(parentId).addPosition(moveDirection * moveMag);
	Contact output = ComponentManager::getColliderById(parentId).resolve();
	if (output.penetration)
	{
		ComponentManager::getTransformById(parentId).addPosition(-moveDirection * output.penetration);
		if (isBouncy)
		{
			if (output.lastAxisOfReflection == 'X')
			{
				moveDirection.x *= -1;
			}
			else if (output.lastAxisOfReflection == 'Y')
			{
				moveDirection.y *= -1;
			}
			currentSpeed += 20.f;
		}
	}
}

void MovementComponent::moveTowards(const sf::Vector2f& movePos)
{
	TransformComponent transform = ComponentManager::getTransformById(parentId);
	moveTowardsVec = movePos - transform.getPosition();
	movingTowards = true;
}

const sf::Vector2f& MovementComponent::getMoveDirection() const
{
	return moveDirection;
}

void MovementComponent::reset()
{
	setMoveDirection(startDirection);
	setCurrentSpeed(startSpeed);
	movingTowards = false;
}

