#pragma once

#include "Movable.h"
#include "Destroyable.h"
#include "Activatable.h"
#include "Sujet.h"
#include "IObservateur.h"

namespace TP3
{
	class Player;
	
	/// <summary>
	/// Classe qui représente n'importe quel ennemi dans le jeu.
	/// </summary>
	/// <seealso cref="Movable" />
	/// <seealso cref="Activatable" />
	/// <seealso cref="Destroyable" />
	/// <seealso cref="Sujet" />
	/// <seealso cref="IObservateur" />
	class Enemy : public Movable, public Activatable, public Destroyable, public Sujet, public IObservateur
	{
	public:		
		/// <summary>
		/// Représente l'état de l'ennemi.
		/// La différence entre "destroyed" et "deactivated" est que, dans le cas
		/// du premier, l'ennemi a été détruit (tous ses points de vie ont été retirés) avant
		/// d'avoir été désactivé.
		/// </summary>
		enum State
		{
			Spawning,
			Moving,
			Destroyed,
			Deactivated
		};

	private:
		static Player* player;

		unsigned int fireRateMS;
		unsigned int defaultLife;
		unsigned int defaultSpeed;
		int collisionDamage;
		int pointsGivenWhenDestroyed;
		sf::Color color;
		State state;

	public:
		static void setPlayer(Player* player);

		unsigned int getFireRate();
		int getPoints();
		State getState();
		const sf::Color& getColor() const;
		int getCollisionDamage() const;

		virtual void damage(const unsigned int life);
		virtual void damage(const unsigned int life, const sf::Color& dammageColor);

		virtual void activate();
		virtual void activate(const sf::Vector2f& position);
		virtual void deactivate();

		virtual void notifier(Sujet* sujet);

		virtual void update(const float deltaT);
		virtual void draw(sf::RenderWindow& window);

		sf::Time fireTimer;

		sf::Time timerDisability;
		bool isDisabled;
		
		/// <summary>
		/// Fait tirer l'ennemi.
		/// </summary>
		virtual void fire() = 0;

	protected:
		Enemy(const ObjectType type, const int fireRate, const unsigned int defaultLife, const float defaultSpeed, const int pointsGiven, const int collisionDamage);
		virtual ~Enemy();
		static Player* getPlayer();

		void setState(const State state);

		void scroll(const float deltaT);

		virtual void reset();

	};
}