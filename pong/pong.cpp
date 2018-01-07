//Standard
#include <iostream>
//SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
//TGUI
#include <TGUI/TGUI.hpp>
//Pong
#include "Ball.h"
#include "ComponentManager.h"
#include "Config.h"
#include "ControlTypeConfig.h"
#include "GUI.h"
#include "Paddle.h"
#include "ScoreKeeper.h"
#include "Settings.h"
#include "SoundManager.h"
#include "Wall.h"

//Function declarations
bool ballIsOutOfBounds(const sf::Vector2u& screenSize);
void changeScoreText(sf::Text& player1Score, sf::Text& player2Score);
void constructDottedLine(sf::VertexArray&, int, int);
void countDownOnGameStart(sf::RenderWindow& window, sf::Clock& clock, sf::VertexArray& lines, sf::Text& player1Score, sf::Text& player2Score);
void createGameObjects(std::vector<GameObject*>& objects, const std::string& p1Control, const std::string& p2Control);
void drawGameScreen(sf::RenderWindow& window, sf::VertexArray& lines, sf::Text& player1Score, sf::Text& player2Score);
int gameLoop(sf::RenderWindow& window, tgui::Gui& gui, const ControlTypeConfig& controlTypes);
void processEvents(sf::Event& event);
void resetObjects(std::vector<GameObject*>& objects);
void runUpdates(float secondsPassed);
void score(sf::Clock& clock, sf::RenderWindow& window, sf::VertexArray& lines, sf::Text& player1Score, sf::Text& player2Score);
void setUpScores(sf::Text& player1Score, sf::Text& player2Score);
void softResetGame(sf::Clock& clock);

//Initialize global variables
Settings settings = Settings("oswald.ttf");
GUI guiManager = GUI(gameLoop);
bool restart = false;
std::vector<GameObject*> objects;

/*Entry point. Set up game and gui. Seed random number generator.*/
int main() 
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT), "Super Pong");
	tgui::Gui gui{ window };
	sf::Text title;

	//Start with title screen
	guiManager.setUpTitleScreen(gui, window, title, settings);

	//Process events from title screen, title screen handles screen transitions after this
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

/*This game loop should be passed to the GUI class, which will call it. Game objects are created and updated here. 
The game can be reset or paused.*/
int gameLoop(sf::RenderWindow& window, tgui::Gui& gui, const ControlTypeConfig& initControl)
{
	createGameObjects(objects, initControl.p1ControlType, initControl.p2ControlType);

	sf::VertexArray lines(sf::Lines);
	sf::Clock clock;

	sf::Text player1Score;
	sf::Text player2Score;

	setUpScores(player1Score, player2Score);

	if (!SoundManager::initialize())
	{
		return -1;
	}

	countDownOnGameStart(window, clock, lines, player1Score, player2Score);

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
			else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::R)
				{
					//"Soft" reset means scores aren't reset but everything else is
					softResetGame(clock);
					break;
				}
				else if (event.key.code == sf::Keyboard::Escape)
				{
					guiManager.runPauseScreen(gui, window);
					clock.restart();
				}
			}
			processEvents(event);
		}

		if (!restart){
			//Plays a "Ball Scored" sound if a score was made
			if (ballIsOutOfBounds(window.getSize()))
			{
				score(clock, window, lines, player1Score, player2Score);
			}

			sf::Time current = clock.getElapsedTime();
			runUpdates(current.asSeconds());
		}	

		clock.restart();

		drawGameScreen(window, lines, player1Score, player2Score);
		window.display();
	}
	return 0;
}

/*Pass events to each player component since only player controlled paddles respond to input*/
void processEvents(sf::Event& event)
{
	for (auto player : ComponentManager::getPlayers())
	{
		player.second->processEvent(event);
	}
}

/*Run updates on each set of updateable components*/
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

/*Build halfway mark of game board*/
void constructDottedLine(sf::VertexArray& lines, int lineLength, int spacing)
{
	float middleOfScreen = Config::SCREEN_WIDTH / 2;
	float currentHeight = 0.f;
	while (currentHeight < Config::SCREEN_HEIGHT)
	{
		currentHeight += spacing;
		//Lines have a start point and an end point
		lines.append(sf::Vector2f(middleOfScreen, currentHeight));
		lines.append(sf::Vector2f(middleOfScreen, lineLength + currentHeight));
		currentHeight += lineLength;
	}
}

/*Set up score strings and reset score tally*/
void setUpScores(sf::Text& player1Score, sf::Text& player2Score)
{
	player1Score.setFont(settings.getFont());
	player1Score.setString(std::to_string(ScoreKeeper::getPlayerScore(1)));
	player1Score.setCharacterSize(48);
	//Score spacings were chosen arbitrarily to look nice
	player1Score.setFillColor(sf::Color::White);
	player1Score.setPosition(Config::SCREEN_WIDTH / 2 - 40, 30);
	
	player2Score.setFont(settings.getFont());
	player2Score.setString(std::to_string(ScoreKeeper::getPlayerScore(2)));
	player2Score.setCharacterSize(48);
	player2Score.setFillColor(sf::Color::White);
	player2Score.setPosition(Config::SCREEN_WIDTH / 2 + 20, 30);

	ScoreKeeper::resetScores();
}

/*Change score text and play sound increase*/
void changeScoreText(sf::Text& player1Score, sf::Text& player2Score)
{
	player1Score.setString(std::to_string(ScoreKeeper::getPlayerScore(1)));
	player2Score.setString(std::to_string(ScoreKeeper::getPlayerScore(2)));
	SoundManager::playScoreIncrease();
}

/*Draws the midway line, all graphic components, and scores 
but doesn't display the screen in case other things need to be drawn.*/
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

/*Integer-izes the amount of time that needs to elapse to equal the duration passed in.
Used to count down the number of seconds until the game starts*/
int countDown(float elapsedTimeInSeconds, float duration)
{
	return (int)ceil(duration - elapsedTimeInSeconds);
}

void createGameObjects(std::vector<GameObject*>& objects, const std::string& p1Control, const std::string& p2Control)
{
	//Ball needs created before the paddles since the paddles need a reference to the ball
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

/*Checks all transforms to see if they're a ball out of bounds
Currently Pong only has one ball but this would make it easier to have multiple balls*/
bool ballIsOutOfBounds(const sf::Vector2u& screenSize)
{
	for (auto transform : ComponentManager::getTransforms())
	{
		/*Result returns 1 if out of bounds on right, 
		-1 if out of bounds on left and 0 if not out of bounds*/
		int result = transform.second->isOutOfBounds(screenSize);
		if (result && ComponentManager::getParentById(transform.first).getType() == "Ball")
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

/*Puts a countdown on the screen so the player has time to get situated*/
void countDownOnGameStart(sf::RenderWindow& window, sf::Clock& clock, sf::VertexArray& lines, sf::Text& player1Score, sf::Text& player2Score) {
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
}

//"Soft" reset means scores aren't reset but everything else is
void softResetGame(sf::Clock& clock) 
{
	resetObjects(objects);
	clock.restart();
	restart = true;
}

void score(sf::Clock& clock, sf::RenderWindow& window, sf::VertexArray& lines, sf::Text& player1Score, sf::Text& player2Score) 
{
	//Acts as a lock, some components act differently if a score has just been made
	ScoreKeeper::setScoreMade(true);
	sf::Time firstPause = clock.getElapsedTime();
	sf::Time lastPause = firstPause;

	/*Spends a half second running updates so the ball can finish moving off screen.
	The lock makes sure the paddles stop moving.*/
	while ((clock.getElapsedTime() - firstPause) < sf::seconds(0.5f))
	{
		runUpdates(lastPause.asSeconds());
		lastPause = clock.getElapsedTime() - lastPause;

		drawGameScreen(window, lines, player1Score, player2Score);
		window.display();
	}

	//Change the score text and play a score increase sound
	changeScoreText(player1Score, player2Score);

	/*Spends 2 seconds drawing the screen without doing any 
	updates to give the player a breather*/
	while (clock.getElapsedTime() - firstPause < sf::seconds(2.0f))
	{
		drawGameScreen(window, lines, player1Score, player2Score);
		window.display();
	}

	ScoreKeeper::setScoreMade(false);
	softResetGame(clock);
}