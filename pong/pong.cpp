#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include "Config.h"
#include "Paddle.h"
#include "Ball.h"
#include "Wall.h"
#include <array>
#include "ScoreKeeper.h"
#include "SoundManager.h"
#include "ComponentManager.h"
#include "Settings.h"

struct ControlTypeConfig
{
	ControlTypeConfig(const std::string& p1, const std::string& p2) : p1ControlType(p1), p2ControlType(p2) {};
	std::string p1ControlType;
	std::string p2ControlType;
};

void constructDottedLine(sf::VertexArray&, int, int);
void createGameObjects(std::vector<GameObject*>& objects, const std::string& p1Control, const std::string& p2Control);
bool ballIsOutOfBounds(const sf::Vector2u& screenSize);
void resetObjects(std::vector<GameObject*>& objects);
void drawGameScreen(sf::RenderWindow& window, sf::VertexArray& lines, sf::Text& player1Score, sf::Text& player2Score);
void drawTitleScreen(tgui::Gui& gui, sf::RenderWindow& window, sf::Text& title);
void drawPlayerConfigScreen(tgui::Gui& gui, sf::RenderWindow& window, sf::Text& title);
void drawPauseScreen(tgui::Gui& gui, sf::RenderWindow& window);
void drawControlsScreen(tgui::Gui& gui);
void pauseScreen(tgui::Gui& gui, sf::RenderWindow& window);
void score(sf::Text& player1Score, sf::Text& player2Score);
int setUpScores(sf::Text& player1Score, sf::Text& player2Score);
void runUpdates(float secondsPassed);
void processEvents(sf::Event& event);
void quitFunction(sf::RenderWindow& window);
int gameLoop(sf::RenderWindow& window, tgui::Gui& gui, const ControlTypeConfig& controlTypes);
void processControlTypes(tgui::Gui& gui, sf::RenderWindow& window);
void blankReturn();
bool goBack;
Settings settings = Settings("oswald.ttf");



int main() 
{
		srand(time(NULL));
		sf::RenderWindow window(sf::VideoMode(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT), "Super Pong");
		tgui::Gui gui{ window };
		sf::Text title;
		drawTitleScreen(gui, window, title);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				gui.handleEvent(event);
			}
			window.clear(sf::Color::Black);
			window.draw(title);
			gui.draw();
			window.display();
		}
	return 0;
}

void processEvents(sf::Event& event)
{
	for (auto player : ComponentManager::getPlayers())
	{
		player.second->processEvent(event);
	}
}

void runUpdates(float secondsPassed)
{
	for (auto player : ComponentManager::getPlayers())
	{
		player.second->update(secondsPassed);
	}

	for (auto ai : ComponentManager::getAIs())
	{
		ai.second->update(secondsPassed);
	}

	for (auto movement : ComponentManager::getMovements())
	{
		movement.second->update(secondsPassed);
	}

	for (auto audio : ComponentManager::getAudios())
	{
		audio.second->update(secondsPassed);
	}
}

void constructDottedLine(sf::VertexArray& lines, int lineLength, int spacing)
{
	float middleOfScreen = Config::SCREEN_WIDTH / 2;
	float currentHeight = 0.f;
	while (currentHeight < Config::SCREEN_HEIGHT)
	{
		currentHeight += spacing;
		lines.append(sf::Vector2f(middleOfScreen, currentHeight));
		lines.append(sf::Vector2f(middleOfScreen, lineLength + currentHeight));
		currentHeight += lineLength;
	}
}

int loadFont(sf::Font& font)
{
	if (!font.loadFromFile("oswald.ttf"))
	{
		return 0;
	}
	return 1;
}

int setUpScores(sf::Text& player1Score, sf::Text& player2Score)
{
	player1Score.setFont(settings.getFont());
	player1Score.setString(std::to_string(ScoreKeeper::getPlayerScore(1)));
	player1Score.setCharacterSize(48);
	player1Score.setPosition(Config::SCREEN_WIDTH / 2 - 40, 30);
	player1Score.setFillColor(sf::Color::White);

	player2Score.setFont(settings.getFont());
	player2Score.setString(std::to_string(ScoreKeeper::getPlayerScore(2)));
	player2Score.setCharacterSize(48);
	player2Score.setFillColor(sf::Color::White);
	player2Score.setPosition(Config::SCREEN_WIDTH / 2 + 20, 30);
	ScoreKeeper::resetScores();
	return 0;
}

void score(sf::Text& player1Score, sf::Text& player2Score)
{
	player1Score.setString(std::to_string(ScoreKeeper::getPlayerScore(1)));
	player2Score.setString(std::to_string(ScoreKeeper::getPlayerScore(2)));
	SoundManager::playScoreIncrease();
}

void drawGameScreen(sf::RenderWindow& window, sf::VertexArray& lines, sf::Text& player1Score, sf::Text& player2Score)
{
	window.clear(sf::Color::Black);
	constructDottedLine(lines, 5, 20);

	auto graphics = ComponentManager::getGraphics();
	for (auto graphic : ComponentManager::getGraphics())
	{
		window.draw(graphic.second->getSprite());
	}

	window.draw(lines);
	window.draw(player1Score);
	window.draw(player2Score);
}

int countDown(float elapsedTimeInSeconds, float duration)
{
	return (int)ceil(duration - elapsedTimeInSeconds);
}

void createGameObjects(std::vector<GameObject*>& objects, const std::string& p1Control, const std::string& p2Control)
{
	Ball* ball = new Ball(Config::SCREEN_WIDTH / 2.f, Config::SCREEN_HEIGHT / 2.f, 15.f, 800.f);
	Paddle* player1 = new Paddle(Config::SCREEN_WIDTH / 15, Config::SCREEN_HEIGHT / 2, 300.f, p1Control, *ball);
	Paddle* player2 = new Paddle(Config::SCREEN_WIDTH - (Config::SCREEN_WIDTH / 15), Config::SCREEN_HEIGHT / 2, 300.f, p2Control, *ball);
	Wall* topWall = new Wall(Config::SCREEN_WIDTH / 2.f, 0.f);
	Wall* botWall = new Wall(Config::SCREEN_WIDTH / 2.f, Config::SCREEN_HEIGHT);
	objects.push_back(ball);
	objects.push_back(player1);
	objects.push_back(player2);
	objects.push_back(topWall);
	objects.push_back(botWall);
}

void resetObjects(std::vector<GameObject*>& objects)
{
	for (auto obj : objects)
	{
		obj->reset();
	}
}

bool ballIsOutOfBounds(const sf::Vector2u& screenSize)
{
	for (auto transform : ComponentManager::getTransforms())
	{
		int result = transform.second->isOutOfBounds(screenSize);
		if (result != 0 && ComponentManager::getParentById(transform.first).getType() == "Ball")
		{
			SoundManager::playBallScored();

			if (result == 1)
			{
				ScoreKeeper::incrementScore(1);
			}
			else if (result == -1)
			{
				ScoreKeeper::incrementScore(2);
			}
			return true;
		}
	}
	return false;
}

void drawPlayerConfigScreen(tgui::Gui& gui, sf::RenderWindow& window, sf::Text& title)
{
	gui.removeAllWidgets();

	tgui::Label::Ptr p1Label = tgui::Label::create();
	p1Label->setPosition(tgui::bindWidth(gui)*0.25, tgui::bindHeight(gui)*0.050);
	p1Label->setText("Left Paddle");
	p1Label->setFont(settings.getFont());
	p1Label->setTextSize(64);
	p1Label->setTextColor(sf::Color::White);
	gui.add(p1Label);

	tgui::Tab::Ptr p1Tabs = tgui::Tab::create();
	p1Tabs->add("P1");
	p1Tabs->add("AI");
	p1Tabs->setPosition(tgui::bindWidth(gui)*0.35, tgui::bindHeight(gui)*0.250);
	p1Tabs->setTabHeight(70);
	gui.add(p1Tabs, "p1Tabs");


	tgui::Label::Ptr p2Label = tgui::Label::create();
	p2Label->setPosition(tgui::bindWidth(gui)*0.25, tgui::bindHeight(gui)*0.400);
	p2Label->setText("Right Paddle");
	p2Label->setFont(settings.getFont());
	p2Label->setTextSize(64);
	p2Label->setTextColor(sf::Color::White);
	gui.add(p2Label);


	tgui::Tab::Ptr p2Tabs = tgui::Tab::create();
	p2Tabs->add("P2");
	p2Tabs->add("AI");
	p2Tabs->setPosition(tgui::bindWidth(gui)*0.35, tgui::bindHeight(gui)*0.600);
	p2Tabs->setTabHeight(70);
	gui.add(p2Tabs, "p2Tabs");

	tgui::Button::Ptr play = tgui::Button::create();
	play->setPosition(tgui::bindWidth(gui)*0.65, tgui::bindHeight(gui)*0.800);
	play->setSize(tgui::bindWidth(gui)*0.3, tgui::bindHeight(gui)*0.15);
	play->setText("OK");
	play->connect("pressed", processControlTypes, std::ref(gui), std::ref(window));
	gui.add(play, "MyButton");


	tgui::Button::Ptr back = tgui::Button::create();
	back->setPosition(tgui::bindWidth(gui)*0.15, tgui::bindHeight(gui)*0.850);
	back->setSize(tgui::bindWidth(gui)*0.2, tgui::bindHeight(gui)*0.1);
	back->setText("Back");
	back->connect("pressed", drawTitleScreen, std::ref(gui), std::ref(window), std::ref(title));
	gui.add(back, "MyButton");
}

void initialize(sf::Font& font) {
	loadFont(font);
}

void processControlTypes(tgui::Gui& gui, sf::RenderWindow& window)
{

	ControlTypeConfig controlTypes = ControlTypeConfig(gui.get<tgui::Tab>("p1Tabs")->getSelected(), gui.get<tgui::Tab>("p2Tabs")->getSelected());
	gameLoop(window, gui, controlTypes);
}

void drawTitleScreen(tgui::Gui& gui, sf::RenderWindow& window, sf::Text& title)
{
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
	play->connect("pressed", drawPlayerConfigScreen, std::ref(gui), std::ref(window), std::ref(title));
	gui.add(play, "MyButton");

	tgui::Button::Ptr quit = tgui::Button::create();
	quit->setPosition(tgui::bindWidth(gui)*0.3, tgui::bindHeight(gui)*0.75);
	quit->setSize(tgui::bindWidth(gui)*0.4, tgui::bindHeight(gui)*0.15);
	quit->setText("Quit");
	quit->connect("pressed", quitFunction, std::ref(window));
	gui.add(quit, "MyButton");
}

void quitFunction(sf::RenderWindow& window)
{
	window.close();
}

void drawPauseScreen(tgui::Gui& gui, sf::RenderWindow& window)
{
	goBack = false;
		pauseScreen(gui, window);
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

void pauseScreen(tgui::Gui& gui, sf::RenderWindow& window)
{
	gui.removeAllWidgets();
	tgui::Button::Ptr set = tgui::Button::create();
	set->setPosition(tgui::bindWidth(gui)*0.3, tgui::bindHeight(gui)*0.100);
	set->setSize(tgui::bindWidth(gui)*0.4, tgui::bindHeight(gui)*0.15);
	set->setText("Settings");
	set->hide();
	set->connect("pressed", quitFunction, std::ref(window));
	gui.add(set, "MyButton");

	tgui::Button::Ptr changePlayers = tgui::Button::create();
	changePlayers->setPosition(tgui::bindWidth(gui)*0.3, tgui::bindHeight(gui)*0.300);
	changePlayers->setSize(tgui::bindWidth(gui)*0.4, tgui::bindHeight(gui)*0.15);
	changePlayers->setText("Change Player Status");
	changePlayers->hide();
	gui.add(changePlayers, "MyButton");

	tgui::Button::Ptr resume = tgui::Button::create();
	resume->setPosition(tgui::bindWidth(gui)*0.3, tgui::bindHeight(gui)*0.500);
	resume->setSize(tgui::bindWidth(gui)*0.4, tgui::bindHeight(gui)*0.15);
	resume->setText("Resume");
	resume->connect("pressed", blankReturn);
	gui.add(resume, "MyButton");

	tgui::Button::Ptr quit = tgui::Button::create();
	quit->setPosition(tgui::bindWidth(gui)*0.3, tgui::bindHeight(gui)*0.800);
	quit->setSize(tgui::bindWidth(gui)*0.4, tgui::bindHeight(gui)*0.15);
	quit->setText("Quit");
	quit->connect("pressed", quitFunction, std::ref(window));
	gui.add(quit, "MyButton");
}

void blankReturn()
{
	goBack = true;
}

int gameLoop(sf::RenderWindow& window, tgui::Gui& gui, const ControlTypeConfig& initControl)
{
	std::vector<GameObject*> objects;
	createGameObjects(objects, initControl.p1ControlType, initControl.p2ControlType);

	sf::Text player1Score;
	sf::Text player2Score;

	setUpScores(player1Score, player2Score);

	sf::VertexArray lines(sf::Lines);
	sf::Clock clock;
	if (!SoundManager::initialize())
	{
		return -1;
	}
	sf::Text countText;
	countText.setFont(settings.getFont());
	countText.setCharacterSize(200);
	countText.setFillColor(sf::Color::Green);
	while (clock.getElapsedTime() < sf::seconds(2.0f))
	{
		countText.setString(std::to_string(countDown(clock.getElapsedTime().asSeconds(), 2.0f)));
		countText.setOrigin(countText.getLocalBounds().width / 2, countText.getLocalBounds().height / 2);
		countText.setPosition(sf::Vector2f(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 3));
		drawGameScreen(window, lines, player1Score, player2Score);
		window.draw(countText);
		window.display();
	}
	clock.restart();
	while (window.isOpen())
	{
		bool restart = false;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::R)
				{
					resetObjects(objects);
					clock.restart();
					restart = true;
					break;
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					drawPauseScreen(gui, window);
					clock.restart();
					sf::Text countText;
					countText.setFont(settings.getFont());
					countText.setCharacterSize(200);
					countText.setFillColor(sf::Color::Green);
					while (clock.getElapsedTime() < sf::seconds(0.f))
					{
						countText.setString(std::to_string(countDown(clock.getElapsedTime().asSeconds(), 1.0f)));
						countText.setOrigin(countText.getLocalBounds().width / 2, countText.getLocalBounds().height / 2);
						countText.setPosition(sf::Vector2f(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 3));
						drawGameScreen(window, lines, player1Score, player2Score);
						window.display();
					}
					clock.restart();
				}
			}
			processEvents(event);
		}

		if (ballIsOutOfBounds(window.getSize()))
		{
			ScoreKeeper::setScoreMade(true);
			sf::Time firstPause = clock.getElapsedTime();
			sf::Time lastPause = firstPause;
			while ((clock.getElapsedTime() - firstPause) < sf::seconds(0.5f))
			{
				runUpdates(lastPause.asSeconds());
				lastPause = clock.getElapsedTime() - lastPause;

				drawGameScreen(window, lines, player1Score, player2Score);
				window.display();
			}

			score(player1Score, player2Score);

			while (clock.getElapsedTime() - firstPause < sf::seconds(2.0f))
			{
				drawGameScreen(window, lines, player1Score, player2Score);
				window.display();
			}

			ScoreKeeper::setScoreMade(false);
			resetObjects(objects);
			clock.restart();
			restart = true;
		}

		if (restart)
		{
			continue;
		}
		sf::Time current = clock.getElapsedTime();
		runUpdates(current.asSeconds());
		clock.restart();

		drawGameScreen(window, lines, player1Score, player2Score);
		window.display();
	}
	return 0;
}