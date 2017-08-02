#include "PlayerController.h"
#include "Paddle.h"
#include <SFML/Window.hpp>


PlayerController::PlayerController(sf::Keyboard::Key up, sf::Keyboard::Key down):
	MoveUpKey(up), MoveDownKey(down)
{
}


PlayerController::~PlayerController()
{
}

void PlayerController::processEvent(sf::Event& event)
{
	if (!parent) {
		return;
	}
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == MoveUpKey)
		{
			this->parent->enableMoveUp();
		}
		else if (event.key.code == MoveDownKey)
		{
			this->parent->enableMoveDown();
		}
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == MoveUpKey)
		{
			this->parent->disableMoveUp();
		}
		else if (event.key.code == MoveDownKey)
		{
			this->parent->disableMoveDown();
		}
	}
}
