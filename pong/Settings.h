#pragma once
#include <SFML/Graphics.hpp>
class Settings
{
public:
	Settings(const std::string& fontFileName);
	~Settings();
	const sf::Font& getFont();
	int loadFont(const std::string& fontFileName);

private:
	sf::Font font;
};

