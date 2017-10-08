#pragma once
#include "GameObject.h"
#include "Config.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "Ball.h"

class Paddle:
	public GameObject
{
	public:
		Paddle(float x, float y, float speedInPixelsPerSecond, const std::string& controlType, const Ball& ball);
		virtual ~Paddle();
		void reset();

	private:
		const float DEFAULT_RECT_HEIGHT = 100.f;
		const float DEFAULT_RECT_WIDTH = DEFAULT_RECT_HEIGHT/2;

};

