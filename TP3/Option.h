#pragma once

#include "Activatable.h"
#include "UserControlled.h"
#include "Player.h"

namespace TP3
{	
	/// <summary>
	/// L'option suit le joueur de manière décalée. Elle tire devant elle de façon
	/// continue afin d'aider le joueur.
	/// </summary>
	/// <seealso cref="UserControlled" />
	/// <seealso cref="Activatable" />
	class Option : public UserControlled, public Activatable
	{
		// Animations -----------------------------------------------------------------------------------
		static const int OPTION_WIDTH = 64;
		static const int OPTION_HEIGHT = 64;

		static const int NBR_ANIM = 4;

		sf::IntRect animation[NBR_ANIM];

		sf::IntRect* currentRect;

		sf::Time timerAnimation;

		static const int MS_PER_FRAME = 125;

		// Logique ----------------------------------------------------------------------------------------
		static const int MS_MOVING_DELAY = 250;

		static const int MS_LIFETIME = 60000;

		static const int MS_BEFORE_COMMAND_REMOVAL = 1000;

		static const int MS_FIRERATE = 500;

		int timeSinceSpawnedInMs;

		sf::Time innerTimer;
		sf::Int32 timeStartedInMs;

		sf::Time fireTimer;
		sf::Time lastTimeShoot;

		TP3::Player* player;
	public:		
		Option();

		bool init(const RessourceManager::key spriteKey, TP3::Player* player);

		void activate(const sf::Vector2f& position);
		virtual void deactivate();

		void update(const float deltaT);
		void draw(sf::RenderWindow& window);

		void adjustIntoMap();

		// Commandes ---------------------------------------------------------		
		void changeDirection(const sf::Vector2f direction);
		void fire();

	private:
		void animate(float deltaT);
	};
}