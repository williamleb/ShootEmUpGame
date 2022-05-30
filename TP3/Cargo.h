#pragma once

#include "Movable.h"
#include "Destroyable.h"
#include "Activatable.h"
#include "RessourceManager.h"

namespace TP3
{	
	/// <summary>
	/// Le Cargo utilise le mod�le "Fabrique" afin de faire appara�tre un ennemi.
	/// Il est repr�sent� dans le jeu comme une base pouvant �tre d�truite.
	/// </summary>
	/// <seealso cref="Movable" />
	/// <seealso cref="Destroyable" />
	/// <seealso cref="Activatable" />
	class Cargo : public Movable, public Destroyable, public Activatable
	{
	public:
		static const int CARGO_WIDTH = 237;
		static const int CARGO_HEIGHT = 128;

	private:
		static const int CARGO_LIFE = 18;

		GameObject::ObjectType typeOfEnnemy;

		const int spawnRate;

		sf::Time timerSpawn;

		sf::IntRect alive;
		sf::IntRect destroyed;

	public:
		void activate();
		void activate(const sf::Vector2f& position);
		
		/// <summary>
		/// Fait appara�tre un nouvel ennemi.
		/// </summary>
		virtual void spawn() = 0;

		void update(const float deltaT);
		void draw(sf::RenderWindow& window);

		bool init(RessourceManager::key spriteKey);

	protected:		
		Cargo(GameObject::ObjectType type, const int spawnRate);
	};
}