#pragma once
#include <SFML/Window.hpp>

class Config
{
public:
	static constexpr float SCREEN_WIDTH = 640.f;
	static constexpr float SCREEN_HEIGHT = 480.f;
	static constexpr sf::Keyboard::Key P1_UP = sf::Keyboard::W;
	static constexpr sf::Keyboard::Key P1_DOWN = sf::Keyboard::S;
	static constexpr sf::Keyboard::Key P2_UP = sf::Keyboard::Up;
	static constexpr sf::Keyboard::Key P2_DOWN = sf::Keyboard::Down;
};

