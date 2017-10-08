#pragma once
#include "Component.h"
#include "Ball.h"

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

