#pragma once

#include "Component.h"

/*Component that causes the object to make sounds on certain conditions.*/
class AudioComponent :
	public Component
{
public:
	AudioComponent(int parentId);
	virtual ~AudioComponent();
	virtual void update(float secondsPassed);
};

