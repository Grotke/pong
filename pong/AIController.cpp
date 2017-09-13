#include "AIController.h"
#include "Vectors.h"
#include "Paddle.h"
#include <cmath>

AIController::AIController(const Ball& ball, float tickRate): 
	ball(ball), timePassedSinceUpdate(0), AITickRate(tickRate)
{
}


AIController::~AIController()
{
}

void AIController::processEvent(sf::Event& event)
{
}

void AIController::update(float secondsPassed)
{
	if (!parent)
	{
		return;
	}
	timePassedSinceUpdate += secondsPassed;
	if (timePassedSinceUpdate >= AITickRate)
	{
		desiredYPosition = updateDesiredYPosition();
		timePassedSinceUpdate = 0;
	}
	int currentPosition = parent->getPosition().y;
	int fudgeFactor = 50;
	if (std::abs(currentPosition - desiredYPosition) <= fudgeFactor)
	{
		parent->disableMoveDown();
		parent->disableMoveUp();
	}

		//float fudgeFactor = 20.f;
		else if (desiredYPosition < currentPosition)
		{
			parent->disableMoveDown();
			parent->enableMoveUp();
		}
		else
		{
			parent->disableMoveUp();
			parent->enableMoveDown();
		}
	//}
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
	if (!parent)
	{
		return false;
	}
	sf::Vector2f& paddleToBall = ball.getPosition() - parent->getPosition();
	float result = Vectors::dot(paddleToBall, ball.getDirection());
	if (result >= 0)
	{
		return false;
	}
	return true;
}
