#pragma once
#include "Component.h"
#include <SFML/Window.hpp>

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

