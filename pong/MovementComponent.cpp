#include "ComponentManager.h"
#include "MovementComponent.h"
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

/*movingTowards is true if the object (a paddle) needs to move towards a point this frame.
The magnitude of the moveTowards vector shows how far away the desired point is.
The paddle moves exactly the magnitude of the moveTowards vector to prevent its normal movement from taking it past the point.
Moving towards something occurs by frame so the bool is reset each frame and 
must be set again using the moveTowards function to continue moving towards a point.
*/
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
		
		//MoveTowards is decided per frame
		movingTowards = false;
	}
	else
	{
		moveMag = secondsPassed * currentSpeed;
	}

	//Make the move and check if it would lead to a collision.
	ComponentManager::getTransformById(parentId).addPosition(moveDirection * moveMag);
	Contact output = ComponentManager::getColliderById(parentId).resolve();
	if (output.penetration)
	{
		ComponentManager::getTransformById(parentId).addPosition(-moveDirection * output.penetration);
		
		/*If bouncy (ie it's the ball), the new direction 
		(effective next frame) is reflected over the 
		axis of reflection given by the Contact to simulate a bounce. 
		The new speed is increased to make the game more interesting.*/
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

			//Speed increase is arbitrary and should probably be a variable
			if (currentSpeed + 20.f > topSpeed) {
				currentSpeed = topSpeed;
			}
			else {
				currentSpeed += 20.f;
			}
		}
	}
}

/*Used by AI to smoothly move towards a point.
The movingTowards bool is reset each frame.*/
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

