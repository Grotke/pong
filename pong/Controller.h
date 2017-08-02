#pragma once
#include <SFML/Window.hpp>
class Paddle;
class Controller
{
	public:
		Controller();
		virtual ~Controller();


		void attachParent(Paddle* parent);
		virtual void processEvent(sf::Event& event) = 0;

	protected:
		Paddle* parent = nullptr;
};

