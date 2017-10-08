#pragma once
#include "Component.h"
class AudioComponent :
	public Component
{
public:
	AudioComponent(int parentId);
	virtual ~AudioComponent();
	virtual void update(float secondsPassed);
};

