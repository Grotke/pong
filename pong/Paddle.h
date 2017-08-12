#pragma once
#include "GameObject.h"
#include "Config.h"
#include "BoxCollider.h"
#include "Controller.h"
#include <SFML/Graphics.hpp>
#include "Collision.h"
class Paddle:
	public GameObject
{
	public:
		Paddle(int x, int y, Controller& control);
		virtual ~Paddle();


		sf::RectangleShape& getSprite();
		void enableMoveUp();
		void disableMoveUp();
		void enableMoveDown();
		void disableMoveDown();
		void update(float secondsPassed, const Collision& c, const BoxCollider& b);
		void reset();

	private:
		sf::RectangleShape sprite;
		float speedInPixelsPerSec = 1000.f;
		bool moveUp = false;
		bool moveDown = false;
		int x;
		int y;
		const float DEFAULT_RECT_HEIGHT = 100.f;
		const float DEFAULT_RECT_WIDTH = DEFAULT_RECT_HEIGHT/2;
		Controller& controller;

};

