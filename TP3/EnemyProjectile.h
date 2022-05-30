#pragma once

#include "Projectile.h"

namespace TP3
{	
	/// <summary>
	/// Représente un projectile ennemi dans le jeu.
	/// </summary>
	/// <seealso cref="Projectile" />
	class EnemyProjectile : public Projectile
	{
		sf::Color color;

	public:
		void damage(const unsigned int life);
		void damage(const unsigned int life, const sf::Color& dammageColor);
		const sf::Color& getColor();

		virtual void activate(const sf::Vector2f& position, const sf::Color& color);

		virtual void draw(sf::RenderWindow& window);

	protected:		
		EnemyProjectile(const ObjectType type, const float speed, const int power = 1, const unsigned int health = Projectile::PROJECTILE_DEFAULT_HEALTH);

	};
}