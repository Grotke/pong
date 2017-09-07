#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Config.h"
#include "Paddle.h"
#include "Ball.h"
#include "Wall.h"
#include "Collider.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "PlayerController.h"
#include "Collision.h"
#include <array>
#include "ScoreKeeper.h"
#include "SoundManager.h"
#include "AIController.h"
void constructDottedLine(sf::VertexArray&, int, int);

int main() 
{
		sf::RenderWindow window(sf::VideoMode(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT), "Super Pong");

		PlayerController p1 = PlayerController(sf::Keyboard::W, sf::Keyboard::S);
		PlayerController p2 = PlayerController(sf::Keyboard::Up, sf::Keyboard::Down);
		Ball ball = Ball(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2);
		AIController a1 = AIController(ball);
		AIController a2 = AIController(ball);
		Paddle player1 = Paddle(Config::SCREEN_WIDTH / 15, Config::SCREEN_HEIGHT / 2, a1);
		Paddle player2 = Paddle(Config::SCREEN_WIDTH - (Config::SCREEN_WIDTH / 15), Config::SCREEN_HEIGHT / 2, a2);
		//Paddle player1 = Paddle(Config::SCREEN_WIDTH / 15, Config::SCREEN_HEIGHT / 2, p1);
		//Paddle player2 = Paddle(Config::SCREEN_WIDTH - (Config::SCREEN_WIDTH / 15), Config::SCREEN_HEIGHT / 2, p2);
		Wall topWall = Wall(Config::SCREEN_WIDTH/2, 0);
		Wall bottomWall = Wall(Config::SCREEN_WIDTH/2, Config::SCREEN_HEIGHT);
		BoxCollider b1(player1.getSprite(), "Paddle");
		BoxCollider b2(player2.getSprite(), "Paddle");
		BoxCollider w1(topWall.getSprite(), "Wall");
		BoxCollider w2(bottomWall.getSprite(), "Wall");
		CircleCollider b3(ball.getSprite(), "Ball");
		sf::Font font;
		sf::Text player1Score;
		sf::Text player2Score;
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


		const std::array<const Collider const *, 5> colliders{ &b1, &b2, &w1, &w2, &b3 };
		Collision c1(colliders);

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
						player1.reset();
						player2.reset();
						ball.reset();
						clock.restart();
						restart = true;
						break;
					}
				}
				p1.processEvent(event);
				p2.processEvent(event);
			}

			if (ball.outOfBounds(window.getSize()))
			{
				//sf::sleep(sf::seconds(0.5f));
				sf::Time firstPause = clock.getElapsedTime();
				sf::Time lastPause = firstPause;
				while ((clock.getElapsedTime() - firstPause) < sf::seconds(0.5f))
				{
					ball.update(lastPause.asSeconds(), c1, b3);
					lastPause = clock.getElapsedTime() - lastPause;

					window.clear(sf::Color::Black);

					constructDottedLine(lines, 5, 20);
					window.draw(lines);
					window.draw(player1.getSprite());
					window.draw(player2.getSprite());
					window.draw(ball.getSprite());
					window.draw(topWall.getSprite());
					window.draw(bottomWall.getSprite());
					window.draw(player1Score);
					window.draw(player2Score);

					window.display();
				}
				player1Score.setString(std::to_string(ScoreKeeper::getPlayerScore(1)));
				player2Score.setString(std::to_string(ScoreKeeper::getPlayerScore(2)));
				SoundManager::playScoreIncrease();

				while (clock.getElapsedTime() - firstPause < sf::seconds(2.0f))
				{
					window.clear(sf::Color::Black);
					constructDottedLine(lines, 5, 20);
					window.draw(lines);
					window.draw(player1.getSprite());
					window.draw(player2.getSprite());
					window.draw(ball.getSprite());
					window.draw(topWall.getSprite());
					window.draw(bottomWall.getSprite());
					window.draw(player1Score);
					window.draw(player2Score);

					window.display();
				}


				player1.reset();
				player2.reset();
				ball.reset();
				clock.restart();
				restart = true;
			}

			if (restart)
			{
				continue;
			}
			sf::Time current = clock.getElapsedTime();
			player1.update(current.asSeconds(), c1, b1);
			player2.update(current.asSeconds(), c1, b2);
			a2.update();
			a1.update();
			ball.update(current.asSeconds(), c1, b3);
			clock.restart();

			window.clear(sf::Color::Black);

			constructDottedLine(lines, 5, 20);
			window.draw(lines);
			window.draw(player1.getSprite());
			window.draw(player2.getSprite());
			window.draw(ball.getSprite());
			window.draw(topWall.getSprite());
			window.draw(bottomWall.getSprite());
			window.draw(player1Score);
			window.draw(player2Score);


			window.display();
		}

	return 0;
}

void constructDottedLine(sf::VertexArray& lines, int lineLength, int spacing)
{
	float middleOfScreen = Config::SCREEN_WIDTH / 2;
	int currentHeight = 0;
	while (currentHeight < Config::SCREEN_HEIGHT)
	{
		currentHeight += spacing;
		lines.append(sf::Vector2f(middleOfScreen, currentHeight));
		lines.append(sf::Vector2f(middleOfScreen, lineLength + currentHeight));
		currentHeight += lineLength;
	}
}