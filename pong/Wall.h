#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Wall:
	public GameObject
{
public:
	Wall(float x, float y);
	virtual ~Wall();
};

