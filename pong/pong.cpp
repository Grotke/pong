#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Config.h"
#include "Paddle.h"
#include "Ball.h"
#include "Wall.h"
#include <array>
#include "ScoreKeeper.h"
#include "SoundManager.h"
#include "ComponentManager.h"

void constructDottedLine(sf::VertexArray&, int, int);
void createGameObjects(std::vector<GameObject*>& objects);
bool ballIsOutOfBounds(const sf::Vector2u& screenSize);
void resetObjects(std::vector<GameObject*>& objects);
void drawScreen(sf::RenderWindow& window, sf::VertexArray& lines, sf::Text& player1Score, sf::Text& player2Score);
void score(sf::Text& player1Score, sf::Text& player2Score);
int setUpScores(sf::Text& player1Score, sf::Text& player2Score, sf::Font& font);
void runUpdates(float secondsPassed);
void processEvents(sf::Event& event);

int main() 
{
		sf::RenderWindow window(sf::VideoMode(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT), "Super Pong");
		
		std::vector<GameObject*> objects;
		createGameObjects(objects);

		

		sf::Font font;
		sf::Text player1Score;
		sf::Text player2Score;

		setUpScores(player1Score, player2Score, font);

		sf::VertexArray lines(sf::Lines);
		sf::Clock clock;
		if (!SoundManager::initialize())
		{
			return -1;
		}
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

					drawScreen(window, lines, player1Score, player2Score);
				}

				score(player1Score, player2Score);

				while (clock.getElapsedTime() - firstPause < sf::seconds(2.0f))
				{
					drawScreen(window, lines, player1Score, player2Score);
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

			drawScreen(window, lines, player1Score, player2Score);
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

int setUpScores(sf::Text& player1Score, sf::Text& player2Score, sf::Font& font)
{
	if (!font.loadFromFile("oswald.ttf"))
	{
		return 1;
	}
	player1Score.setFont(font);
	player1Score.setString(std::to_string(ScoreKeeper::getPlayerScore(1)));
	player1Score.setCharacterSize(48);
	//text.setStyle(sf::Text::Bold);
	player1Score.setPosition(Config::SCREEN_WIDTH / 2 - 40, 30);
	player1Score.setFillColor(sf::Color::White);

	player2Score.setFont(font);
	player2Score.setString(std::to_string(ScoreKeeper::getPlayerScore(2)));
	player2Score.setCharacterSize(48);
	//text.setStyle(sf::Text::Bold);
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

void drawScreen(sf::RenderWindow& window, sf::VertexArray& lines, sf::Text& player1Score, sf::Text& player2Score)
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
	window.display();
}

void createGameObjects(std::vector<GameObject*>& objects)
{
	Ball* ball = new Ball(Config::SCREEN_WIDTH / 2.f, Config::SCREEN_HEIGHT / 2.f, 25.f, 300);
	Paddle* player1 = new Paddle(Config::SCREEN_WIDTH / 15, Config::SCREEN_HEIGHT / 2, 300.f, "P1", *ball);
	Paddle* player2 = new Paddle(Config::SCREEN_WIDTH - (Config::SCREEN_WIDTH / 15), Config::SCREEN_HEIGHT / 2, 300.f, "P2", *ball);
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