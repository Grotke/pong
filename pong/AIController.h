#pragma once
#include "Controller.h"
#include "Ball.h"
#include <SFML/Graphics.hpp>
class AIController :
	public Controller
{
public:
	AIController(const Ball& ball, float tickRate);
	virtual ~AIController();

	virtual void processEvent(sf::Event& event);
	bool ballIsHeadingTowardsMe();
	void update(float secondsPassed);
	int updateDesiredYPosition();

private:
	const Ball& ball;
	int desiredYPosition;
	float timePassedSinceUpdate;
	float AITickRate;
};

