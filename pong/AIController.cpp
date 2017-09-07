#include "AIController.h"
#include "Vectors.h"
#include "Paddle.h"

AIController::AIController(const Ball& ball): ball(ball)
{
}


AIController::~AIController()
{
}

void AIController::processEvent(sf::Event& event)
{
}

void AIController::update()
{
	if (!parent)
	{
		return;
	}
	desiredYPosition = updateDesiredYPosition();
	int currentPosition = parent->getPosition().y;
	if (currentPosition == desiredYPosition)
	{
		parent->disableMoveDown();
		parent->disableMoveUp();
	}
	else
	{
		if (desiredYPosition < currentPosition)
		{
			parent->disableMoveDown();
			parent->enableMoveUp();
		}
		else
		{
			parent->disableMoveUp();
			parent->enableMoveDown();
		}
	}
}

int AIController::updateDesiredYPosition()
{
	if (ballIsHeadingTowardsMe())
	{
		return ball.getPosition().y;
	}
	else
	{
		return parent->getStartY();
	}
}

bool AIController::ballIsHeadingTowardsMe()
{
	sf::Vector2f& paddleToBall = ball.getPosition() - parent->getPosition();
	float result = Vectors::dot(paddleToBall, ball.getDirection());
	if (result >= 0)
	{
		return false;
	}
	return true;
}
