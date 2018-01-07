#pragma once

#include <SFML/Graphics.hpp>

/*This class holds information that gets 
used across multiple sections of code.
What decides what's handled by this class and 
what's handled by the Config class? 
I'm not sure what I intended with 
having two different places for settings.
They could probably be consolidated into one class.

For the moment, it loads the game's font and 
makes it available to other code.*/
class Settings
{
public:
	Settings(const std::string& fontFileName);
	~Settings();
	const sf::Font& getFont() const;
	int loadFont(const std::string& fontFileName);

private:
	sf::Font font;
};