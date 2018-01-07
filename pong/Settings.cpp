#include "Settings.h"

Settings::Settings(const std::string& fontFileName)
{
	loadFont(fontFileName);
}

Settings::~Settings()
{
}

int Settings::loadFont(const std::string& fontFileName)
{
	if (!font.loadFromFile(fontFileName))
	{
		return 0;
	}
	return 1;
}

const sf::Font& Settings::getFont() const
{
	return font;
}
