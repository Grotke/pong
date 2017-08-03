#include <SFML/Graphics.hpp>
#include <iostream>
#include "Config.h"
#include "Paddle.h"
#include "Ball.h"
#include "Wall.h"
#include "PlayerController.h"
void constructDottedLine(sf::VertexArray&, int, int);

int main() 
{
		sf::RenderWindow window(sf::VideoMode(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT), "Super Pong");

		PlayerController p1 = PlayerController(sf::Keyboard::W, sf::Keyboard::S);
		PlayerController p2 = PlayerController(sf::Keyboard::Up, sf::Keyboard::Down);
		Paddle player1 = Paddle(Config::SCREEN_WIDTH / 15, Config::SCREEN_HEIGHT / 2, p1);
		Paddle player2 = Paddle(Config::SCREEN_WIDTH - (Config::SCREEN_WIDTH / 15), Config::SCREEN_HEIGHT / 2, p2);
		Ball ball = Ball(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2);
		Wall topWall = Wall(Config::SCREEN_WIDTH/2, 0);
		Wall bottomWall = Wall(Config::SCREEN_WIDTH/2, Config::SCREEN_HEIGHT);
		sf::VertexArray lines(sf::Lines);
		sf::Clock clock;

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
			player1.update(current.asSeconds());
			player2.update(current.asSeconds());
			ball.update(current.asSeconds());
			clock.restart();

			window.clear(sf::Color::Black);

			constructDottedLine(lines, 5, 20);
			window.draw(lines);
			window.draw(player1.getSprite());
			window.draw(player2.getSprite());
			window.draw(ball.getSprite());
			window.draw(topWall.getSprite());
			window.draw(bottomWall.getSprite());


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