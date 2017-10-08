#include "AIComponent.h"
#include "ComponentManager.h"
#include "Vectors.h"
#include "ScoreKeeper.h"



AIComponent::AIComponent(int parentId, int inBallId)
	: Component(parentId), ballId(inBallId)
{
	previousDesiredY = ComponentManager::getTransformById(parentId).getPosition().y;
}


AIComponent::~AIComponent()
{
}

void AIComponent::update(float secondsPassed)
{
	if (!ScoreKeeper::scoreWasMade())
	{
		float desiredYPosition = updateDesiredYPosition();
		float x = ComponentManager::getTransformById(parentId).getPosition().x;
		ComponentManager::getMovementById(parentId).moveTowards(sf::Vector2f(x, desiredYPosition));
	}
}

bool AIComponent::ballIsHeadingTowardsMe() const
{
	sf::Vector2f paddleToBall = ComponentManager::getTransformById(ballId).getPosition() - ComponentManager::getTransformById(parentId).getPosition();
	float result = Vectors::dot(paddleToBall, ComponentManager::getMovementById(ballId).getMoveDirection());
	if (result >= 0)
	{
		return false;
	}
	return true;
}

float AIComponent::updateDesiredYPosition()
{
	if (ballIsHeadingTowardsMe())
	{
		previousDesiredY = ComponentManager::getTransformById(ballId).getPosition().y;
	}
	return previousDesiredY;
}
