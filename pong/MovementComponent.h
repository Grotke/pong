#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"

/*This component allows the game object to move.
It assumes the object has a collider 
and it doesn't bother checking for one before trying to access it.
This should be changed eventually.
The object has a start speed (for resetting) and a max speed. 
The object also needs to be specified as "bouncy" or not. 
Basically if it's a ball and not a paddle. 
This changes how the object responds to a collision.
The bouncy parameter should probably be with the collider.
moveTowards is used by the AI to move towards a point 
(player controlled paddles move in a direction rather than to a point).*/
class MovementComponent :
	public Component
{
	public:
		MovementComponent(int parentId, const sf::Vector2f& startDir, float startSpeed, float topSpeed, bool isBouncy);
		virtual ~MovementComponent();
		void moveTowards(const sf::Vector2f& movePos);
		void setMoveDirection(const sf::Vector2f& newMoveDir);
		const sf::Vector2f& getMoveDirection() const;
		void setCurrentSpeed(float newSpeed);
		void update(float secondsPassed);
		void reset();

	private:
		sf::Vector2f startDirection;
		float startSpeed;
		float currentSpeed;
		float topSpeed;
		sf::Vector2f moveDirection;
		sf::Vector2f moveTowardsVec;
		bool movingTowards;
		bool isBouncy;
};


