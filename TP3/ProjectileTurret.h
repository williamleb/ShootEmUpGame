#pragma once
#include "Movable.h"
#include "RessourceManager.h"
#include "Activatable.h"
#include "EnemyProjectile.h"

namespace TP3
{
	/// <summary>
	/// projectile tiré par les tourelles.
	/// </summary>
	/// <seealso cref="Movable" />
	class ProjectileTurret : public EnemyProjectile
	{
		static const int PROJECTILE_WIDTH = 100;
		static const int PROJECTILE_HEIGHT = 100;

		static const int PROJECTILE_SPEED = 500;
		

	public:
		ProjectileTurret();
		ProjectileTurret(Direction direction, const sf::Vector2f& position);
		void draw(sf::RenderWindow &window);
		void init(RessourceManager::key spriteKey);
		void update(const float deltaT);
		void activate(const sf::Vector2f& position);
		void setDirection(const float angle);
		void setDirection(const Direction direction);
		void setDirection(sf::Vector2f direction);
	};
}
