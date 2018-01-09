#pragma once

#include "Ball.h"
#include "Component.h"

/*This component attaches an AI to a paddle. 
It needs the ball's ID from the component manager 
since it tracks the ball position.*/
class AIComponent :
	public Component
{
public:
	AIComponent(int parentId, int inBallId);
	void update(float secondsPassed);
	virtual ~AIComponent();

private:
	bool ballIsHeadingTowardsMe() const;
	float updateDesiredYPosition();
	float previousDesiredY;
	int ballId;
};

