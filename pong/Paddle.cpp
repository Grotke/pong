#include "Paddle.h"
#include "Config.h"
#include <SFML/Graphics.hpp>
#include "ComponentManager.h"



Paddle::Paddle(float x, float y, float speedInPixelsPerSecond, const std::string& controlType, const Ball& ball)
	: GameObject("Paddle"), prevControl(controlType)
{
	ComponentManager::addTransformTo(*this, sf::Vector2f(x, y), DEFAULT_RECT_HEIGHT, DEFAULT_RECT_WIDTH);
	ComponentManager::addColliderTo(*this);
	ComponentManager::addMovementTo(*this, sf::Vector2f(0.f, 0.f), speedInPixelsPerSecond, speedInPixelsPerSecond, false);
	ComponentManager::addGraphicTo(*this, false);
	addControlComponent(controlType, ball);
}


Paddle::~Paddle()
{
}

void Paddle::reset()
{
	ComponentManager::getTransformByParent(*this).reset();
	ComponentManager::getMovementByParent(*this).reset();
}

void Paddle::addControlComponent(const std::string& controlType, const Ball& ball)
{
	if (controlType == "P1")
	{
		ComponentManager::addPlayerTo(*this, Config::P1_UP, Config::P1_DOWN);
	}
	else if (controlType == "P2")
	{
		ComponentManager::addPlayerTo(*this, Config::P2_UP, Config::P2_DOWN);
	}
	else if (controlType == "AI")
	{
		ComponentManager::addAITo(*this, ball);
	}
	else {

	}
}

void Paddle::replaceControlComponent(const std::string& newControlType, const Ball& ball)
{
	ComponentManager::removeControlComponents(*this);
	addControlComponent(newControlType, ball);
}


