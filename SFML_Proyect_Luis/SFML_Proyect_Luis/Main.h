#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Game
{
	public:
		//Game();
		//void run();

	private:
		bool mIsMovingUp = false;
		bool mIsMovingDown = false;
		bool mIsMovingLeft = false;
		bool mIsMovingRight = false;
		float PlayerSpeed = 350.5f;
		sf::Time TimePerFrame = sf::seconds(1.0f/60.0f);

		
		//void processEvents();
		//void update(sf::Time _deltaTime);
		//void render();
		//void handlePlayerInput(sf::Keyboard::Key _key, bool _isPressed);

		sf::RenderWindow mWindow;
		sf::CircleShape mPlayer;
};