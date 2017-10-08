#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
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


