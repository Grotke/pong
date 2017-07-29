#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Paddle.h"
#include "Ball.h"
#include "Wall.h"

void constructDottedLine(sf::VertexArray&, int, int);

int main() {
	sf::RenderWindow window(sf::VideoMode(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT), "Super Pong");

	Paddle player1 = Paddle(Config::SCREEN_WIDTH/15, Config::SCREEN_HEIGHT/2);
	Paddle player2 = Paddle(Config::SCREEN_WIDTH - (Config::SCREEN_WIDTH / 15), Config::SCREEN_HEIGHT / 2);
	Ball ball = Ball(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2);
	Wall topWall = Wall(0, 0);
	Wall bottomWall = Wall(0, Config::SCREEN_HEIGHT - 20);
	sf::VertexArray lines(sf::Lines);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

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