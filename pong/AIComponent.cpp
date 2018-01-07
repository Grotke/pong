#include "AIComponent.h"
#include "ComponentManager.h"
#include "ScoreKeeper.h"
#include "Vectors.h"

AIComponent::AIComponent(int parentId, int inBallId)
	: Component(parentId), ballId(inBallId)
{
	previousDesiredY = ComponentManager::getTransformById(parentId).getPosition().y;
}

AIComponent::~AIComponent()
{
}

//Moves towards the Y position of the ball while a score hasn't been made.
void AIComponent::update(float secondsPassed)
{
	if (!ScoreKeeper::scoreWasMade())
	{
		float desiredYPosition = updateDesiredYPosition();
		float x = ComponentManager::getTransformById(parentId).getPosition().x;
		ComponentManager::getMovementById(parentId).moveTowards(sf::Vector2f(x, desiredYPosition));
	}
	else {
		//Stop paddle from moving after scoring. Without this, it'll continue to move after scoring.
		ComponentManager::getMovementById(parentId).setCurrentSpeed(0.f);
	}
}

//Checks if ball is heading in direction of paddle
bool AIComponent::ballIsHeadingTowardsMe() const
{
	sf::Vector2f paddleFrontDir = ComponentManager::getTransformById(ballId).getPosition() - ComponentManager::getTransformById(parentId).getPosition();
	float result = Vectors::dot(paddleFrontDir, ComponentManager::getMovementById(ballId).getMoveDirection());
	if (result >= 0)
	{
		return false;
	}
	return true;
}

//Tracks ball only if heading in direction of paddle. Otherwise stays still.
float AIComponent::updateDesiredYPosition()
{
	if (ballIsHeadingTowardsMe())
	{
		previousDesiredY = ComponentManager::getTransformById(ballId).getPosition().y;
	}
	return previousDesiredY;
}
