#pragma once
#include "Destroyable.h"
#include "RessourceManager.h"
#include "Inputs.h"
#include "Shield.h"
#include "UserControlled.h"
#include "Weapon.h"
#include "IObservateur.h"
#include "Structures\stack.h"

namespace TP3
{	
	/// <summary>
	/// Représente le vaisseau du joueur dans le jeu.
	/// </summary>
	/// <seealso cref="UserControlled" />
	/// <seealso cref="IObservateur" />
	/// <seealso cref="Sujet" />
	/// <seealso cref="Movable" />
	/// <seealso cref="Destroyable" />
	class Player : public UserControlled, public Destroyable, public IObservateur, public Sujet
	{
		
		// Animations -----------------------------------------------------------------------------------
		static const int ANIM_RECT_WIDTH = 90;
		static const int ANIM_RECT_HEIGHT = 48;

		static const int NBR_ANIM = 5;
		static const int ANIM_IDLE_POSITION = 2;
			
		sf::IntRect animation[NBR_ANIM];

		sf::IntRect* currentRect;

		sf::Time timerAnimation;

		sf::Time timerDisability;
		bool isDisabled;

		// Logique --------------------------------------------------------------------------------------
	public:
		static const int PLAYER_DEFAULT_LIFE = 10;
		static const int PLAYER_DEFAULT_SPEED = 500;

	private:
		static const int SHIELD_WIDTH = 160;
		static const int SHIELD_HEIGHT = 160;

		static const int MS_BEFORE_COMMAND_REMOVAL = 1000;

		static const int MS_PER_FRAME = 200;

		TP3_structures::stack<Shield*> shields;
		RessourceManager::key shieldSpriteKey;
		

		static Inputs inputs;

		Weapon* currentWeapon;

		static const int MS_BEFORE_FLASHING_INVINCIBILITY = 500;
		bool isInvincible;
		sf::Time timerOFInvincibility;
		sf::Time animationInvincibility;

	public:		
		Player();
		~Player();
		
		bool init(const RessourceManager::key spriteKey, const RessourceManager::key shieldSpriteKey);
		void getInputs();
		void update(const float deltaT);
		void draw(sf::RenderWindow& window);

		void damage(const unsigned int life);
		void damage(const unsigned int life, const sf::Color& dammageColor);

		void changeWeapon(Weapon* weapon);

		void notifier(Sujet* sujet);

		unsigned int getLastShieldLife() const;

		void setInvincivility(const unsigned int milliseconds);

		// Commandes ---------------------------------------------------------		
		void changeDirection(const sf::Vector2f direction);
		void fire();

		static Inputs& getPlayerInputs();


	protected:

		Movable::Direction getDirectionFromInput(int moveMap);
				
		void adjustIntoMap();

	private:
		void animate(const float deltaT);
	};
}