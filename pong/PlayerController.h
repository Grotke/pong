#pragma once
#include "Controller.h"
#include <SFML/Window.hpp>
class PlayerController :
	public Controller
{
public:
	PlayerController(sf::Keyboard::Key up, sf::Keyboard::Key down);
	~PlayerController();

	void processEvent(sf::Event& event) override;

private:
	sf::Keyboard::Key MoveUpKey;
	sf::Keyboard::Key MoveDownKey;
};

