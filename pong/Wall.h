#pragma once

#include "GameObject.h"

/*Wall that borders top and bottom of screen.*/
class Wall:
	public GameObject
{
public:
	Wall(float x, float y);
	virtual ~Wall();
};

