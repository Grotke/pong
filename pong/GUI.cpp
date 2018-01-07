#include "ControlTypeConfig.h"
#include "GUI.h"

GUI::GUI(int (*ptrToGameLoop)(sf::RenderWindow&, tgui::Gui&, const ControlTypeConfig&)): gameLoopPtr(ptrToGameLoop)
{
}

GUI::~GUI()
{
}

/*This menu allows you to choose which paddle is AI controlled or Player controlled.*/
void GUI::setUpPlayerConfigScreen(tgui::Gui& gui, sf::RenderWindow& window, sf::Text& title, const Settings& settings)
{
	//In units relative to screen
	float labelHorizPos = 0.25;
	float tabsHorizPos = 0.35;

	//Clear previous gui elements
	gui.removeAllWidgets();

	/*Player 1 label and choices.*/
	tgui::Label::Ptr p1Label = tgui::Label::create();
	p1Label->setPosition(tgui::bindWidth(gui)*labelHorizPos, tgui::bindHeight(gui)*0.050);
	p1Label->setText("Left Paddle");
	p1Label->setFont(settings.getFont());
	p1Label->setTextSize(64);
	p1Label->setTextColor(sf::Color::White);
	gui.add(p1Label);

	tgui::Tab::Ptr p1Tabs = tgui::Tab::create();
	p1Tabs->add("P1");
	p1Tabs->add("AI");
	p1Tabs->setPosition(tgui::bindWidth(gui)*tabsHorizPos, tgui::bindHeight(gui)*0.250);
	p1Tabs->setTabHeight(70);
	gui.add(p1Tabs, "p1Tabs");

	/*Player 2 label and choices*/
	tgui::Label::Ptr p2Label = tgui::Label::create();
	p2Label->setPosition(tgui::bindWidth(gui)*labelHorizPos, tgui::bindHeight(gui)*0.400);
	p2Label->setText("Right Paddle");
	p2Label->setFont(settings.getFont());
	p2Label->setTextSize(64);
	p2Label->setTextColor(sf::Color::White);
	gui.add(p2Label);

	tgui::Tab::Ptr p2Tabs = tgui::Tab::create();
	p2Tabs->add("P2");
	p2Tabs->add("AI");
	p2Tabs->setPosition(tgui::bindWidth(gui)*tabsHorizPos, tgui::bindHeight(gui)*0.600);
	p2Tabs->setTabHeight(70);
	gui.add(p2Tabs, "p2Tabs");

	/*Navigation buttons to play or go to previous screen.*/
	tgui::Button::Ptr play = tgui::Button::create();
	play->setPosition(tgui::bindWidth(gui)*0.65, tgui::bindHeight(gui)*0.800);
	play->setSize(tgui::bindWidth(gui)*0.3, tgui::bindHeight(gui)*0.15);
	play->setText("OK");
	play->connect("pressed", &GUI::processControlTypes, this, std::ref(gui), std::ref(window));
	gui.add(play, "MyButton");

	tgui::Button::Ptr back = tgui::Button::create();
	back->setPosition(tgui::bindWidth(gui)*0.15, tgui::bindHeight(gui)*0.850);
	back->setSize(tgui::bindWidth(gui)*0.2, tgui::bindHeight(gui)*0.1);
	back->setText("Back");
	back->connect("pressed", &GUI::setUpTitleScreen, this, std::ref(gui), std::ref(window), std::ref(title), std::ref(settings));
	gui.add(back, "MyButton");
}

void GUI::setUpPauseScreen(tgui::Gui& gui, sf::RenderWindow& window)
{
	//Clear previous GUI elements
	gui.removeAllWidgets();

	//Resumes game
	tgui::Button::Ptr resume = tgui::Button::create();
	resume->setPosition(tgui::bindWidth(gui)*0.3, tgui::bindHeight(gui)*0.500);
	resume->setSize(tgui::bindWidth(gui)*0.4, tgui::bindHeight(gui)*0.15);
	resume->setText("Resume");
	resume->connect("pressed", &GUI::blankReturn, this);
	gui.add(resume, "MyButton");

	//Quit game
	tgui::Button::Ptr quit = tgui::Button::create();
	quit->setPosition(tgui::bindWidth(gui)*0.3, tgui::bindHeight(gui)*0.800);
	quit->setSize(tgui::bindWidth(gui)*0.4, tgui::bindHeight(gui)*0.15);
	quit->setText("Quit");
	quit->connect("pressed", &GUI::quitGame, this, std::ref(window));
	gui.add(quit, "MyButton");
}

void GUI::setUpTitleScreen(tgui::Gui& gui, sf::RenderWindow& window, sf::Text& title, const Settings& settings)
{
	//Clear previous GUI elements
	gui.removeAllWidgets();

	tgui::Label::Ptr titleLabel = tgui::Label::create();
	titleLabel->setPosition(tgui::bindWidth(gui)*0.32, tgui::bindHeight(gui)*0.10);
	titleLabel->setText("PONG");
	titleLabel->setFont(settings.getFont());
	titleLabel->setTextSize(104);
	titleLabel->setTextColor(sf::Color::White);
	gui.add(titleLabel);

	tgui::Button::Ptr play = tgui::Button::create();
	play->setPosition(tgui::bindWidth(gui)*0.3, tgui::bindHeight(gui)*0.50);
	play->setSize(tgui::bindWidth(gui)*0.4, tgui::bindHeight(gui)*0.15);
	play->setText("Play");
	play->connect("pressed", &GUI::setUpPlayerConfigScreen, this, std::ref(gui), std::ref(window), std::ref(title), std::ref(settings));
	gui.add(play, "MyButton");

	tgui::Button::Ptr quit = tgui::Button::create();
	quit->setPosition(tgui::bindWidth(gui)*0.3, tgui::bindHeight(gui)*0.75);
	quit->setSize(tgui::bindWidth(gui)*0.4, tgui::bindHeight(gui)*0.15);
	quit->setText("Quit");
	quit->connect("pressed", &GUI::quitGame, this, std::ref(window));
	gui.add(quit, "MyButton");
}

/*Pause screen can be exited through a button or the ESC key. 
This loop is to handle the ESC key.*/
void GUI::runPauseScreen(tgui::Gui& gui, sf::RenderWindow& window)
{
	goBack = false;
	setUpPauseScreen(gui, window);
	while (window.isOpen() && goBack == false)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					return;
				}
			}
			gui.handleEvent(event);
		}
		window.clear(sf::Color::Black);
		gui.draw();
		window.display();
	}
}

void GUI::quitGame(sf::RenderWindow& window)
{
	window.close();
}

/*Quits the current menu without going to another menu.
Should go back to the previous menu or back to the game.*/
void GUI::blankReturn()
{
	goBack = true;
}

/*Pulls the paddle control info from the playerConfig menu and sends it to the game loop.*/
void GUI::processControlTypes(tgui::Gui& gui, sf::RenderWindow& window)
{
	ControlTypeConfig controlTypes = ControlTypeConfig(gui.get<tgui::Tab>("p1Tabs")->getSelected(), gui.get<tgui::Tab>("p2Tabs")->getSelected());
	gameLoopPtr(window, gui, controlTypes);
}