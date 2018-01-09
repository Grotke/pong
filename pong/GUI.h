#pragma once

#include <TGUI/TGUI.hpp>

#include "ControlTypeConfig.h"
#include "Settings.h"



/*Manages the menu screens and the transitions between them.
A game loop function is passed in to allow 
the transition from a menu to the game.*/
class GUI
{
public:
	GUI(int (*ptrToGameLoop)(sf::RenderWindow&, tgui::Gui&, const ControlTypeConfig&));
	~GUI();

	void setUpTitleScreen(tgui::Gui& gui, sf::RenderWindow& window, sf::Text& title, const Settings& settings);
	void setUpPlayerConfigScreen(tgui::Gui& gui, sf::RenderWindow& window, sf::Text& title, const Settings& settings);
	void setUpPauseScreen(tgui::Gui& gui, sf::RenderWindow& window);
	void runPauseScreen(tgui::Gui& gui, sf::RenderWindow& window);
	void quitGame(sf::RenderWindow& window);
	void blankReturn();
	void processControlTypes(tgui::Gui& gui, sf::RenderWindow& window);

private:
	bool goBack;
	int (*gameLoopPtr)(sf::RenderWindow&, tgui::Gui&, const ControlTypeConfig&);
};