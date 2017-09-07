#pragma once
#include "Controller.h"
#include "Ball.h"
#include <SFML/Graphics.hpp>
class AIController :
	public Controller
{
public:
	AIController(const Ball& ball);
	virtual ~AIController();

	virtual void processEvent(sf::Event& event);
	bool ballIsHeadingTowardsMe();
	void update();
	int updateDesiredYPosition();

private:
	const Ball& ball;
	int desiredYPosition;
};

