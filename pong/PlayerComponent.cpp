#include "PlayerComponent.h"
#include "ComponentManager.h"
#include "ScoreKeeper.h"



PlayerComponent::PlayerComponent(int parentId, sf::Keyboard::Key inUpKey, sf::Keyboard::Key inDownKey)
	: Component(parentId), upKey(inUpKey), downKey(inDownKey)
{
	goingUp = false;
	goingDown = false;
}


PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::update(float secondsPassed)
{
	if (ScoreKeeper::scoreWasMade())
	{
		goingUp = false;
		goingDown = false;
	}
	if (!(goingUp ^ goingDown))
	{
		ComponentManager::getMovementById(parentId).setMoveDirection(sf::Vector2f(0.f, 0.f));
	}
	else if (goingUp)
	{
		ComponentManager::getMovementById(parentId).setMoveDirection(sf::Vector2f(0.f, -1.f));
	}
	else
	{
		ComponentManager::getMovementById(parentId).setMoveDirection(sf::Vector2f(0.f, 1.f));
	}
}

void PlayerComponent::processEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == upKey)
		{
			goingUp = true;
		}
		else if (event.key.code == downKey)
		{
			goingDown = true;
		}
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == upKey)
		{
			goingUp = false;
		}
		else if (event.key.code == downKey)
		{
			goingDown = false;
		}
	}
}
