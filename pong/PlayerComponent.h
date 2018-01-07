#pragma once

#include <SFML/Window.hpp>

#include "Component.h"

/*This component allows a human to control a paddle.
It shouldn't be attached to the same object as an AIComponent.
The Up and Down keys are configurable.*/
class PlayerComponent :
	public Component
{
	public:
		PlayerComponent(int parentId, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey);
		virtual ~PlayerComponent();
		void update(float secondsPassed);
		void processEvent(const sf::Event& event);

	private:
		sf::Keyboard::Key upKey;
		sf::Keyboard::Key downKey;
		bool goingUp;
		bool goingDown;
};

