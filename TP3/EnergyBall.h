#pragma once
#include "RessourceManager.h"
#include "EnemyProjectile.h"

namespace TP3
{	
	/// <summary>
	/// L'EnergyBall est un projectile ennemi.
	/// Lorsqu'elle est activée, elle a un délais avant de se mettre à bouger, puis,
	/// elle suit la même direction.
	/// </summary>
	/// <seealso cref="EnemyProjectile" />
	class EnergyBall : public EnemyProjectile
	{
		static const int ENERGY_BALL_SPEED = 500;
		static const int ENERGY_BALL_POWER = 1;
		static const int ENERGY_BALL_HEALTH = 3;

		static const int ENERGY_BALL_WIDTH = 24;
		static const int ENERGY_BALL_HEIGHT = 24;

		static const int MS_BEFORE_MOVE = 600;

		sf::Time moveTimer;

	public:
		EnergyBall();
		void init(RessourceManager::key spriteKey);

		void activate(const sf::Vector2f& position, const sf::Color& color);

		void update(const float deltaT);
	};
}
