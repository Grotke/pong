#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "Ball.h"
#include "Config.h"
#include "GameObject.h"

/*Attaches components to the paddle and 
manages the swapping of AI or player controllers.*/
class Paddle:
	public GameObject
{
	public:
		Paddle(float x, float y, float speedInPixelsPerSecond, const std::string& controlType, const Ball& ball);
		virtual ~Paddle();
		void reset();
		void addControlComponent(const std::string& controlType, const Ball& ball);
		void replaceControlComponent(const std::string& newControlType, const Ball& ball);

	private:
		/*Hardcoded constants should be 
		moved outside the code at some point.*/
		const float DEFAULT_RECT_HEIGHT = 70.f;
		const float DEFAULT_RECT_WIDTH = DEFAULT_RECT_HEIGHT/2;
		std::string prevControl;
};