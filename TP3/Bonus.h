#pragma once

#include "Movable.h"
#include "Activatable.h"
#include "Sujet.h"
#include "RessourceManager.h"

namespace TP3
{	
	/// <summary>
	/// On bonus qui, une fois rammassé, affecte le jeu.
	/// </summary>
	/// <seealso cref="Movable" />
	/// <seealso cref="Activatable" />
	/// <seealso cref="Sujet" />
	class Bonus : public Movable, public Activatable, public Sujet
	{

		static const int MS_LIFETIME = 12000;

		static const int BONUS_WIDTH = 50;
		static const int BONUS_HEIGHT = 50;

		sf::Time innerTimer;

		const GameObject* picker;

	public:		
		virtual ~Bonus();

		void activate();
		void activate(const sf::Vector2f& position);
		
		void update(const float deltaT);
		void draw(sf::RenderWindow& window);

		bool init(RessourceManager::key spriteKey);

		void pick(const GameObject* picker);

		const GameObject* getPicker() const;

	protected:
		Bonus(const GameObject::ObjectType type);
	};
}