#pragma once
#include "Projectile.h"

namespace TP3
{
	/// <summary>
	/// Crée un projectile allié de type Twist.
	/// Le Twist est fait en "rond" et a une trajectoire sinusoïdale.
	/// </summary>
	/// <seealso cref="Projectile" />
	class Twist : public Projectile
	{
	private:
		static const int TWIST_SPEED = 350;
		static const int TWIST_POWER = 1;
		static const int TWIST_HEALTH = 3;

		static const int TWIST_WIDTH = 28;
		static const int TWIST_HEIGHT = 28;

		static const int AMPLITUDE = 100;
		static const float WAVE_SPEED;

		float waveX;

		float posY;

	public:
		Twist();
		void init(RessourceManager::key spriteKey);
		void update(const float deltaT);
		void activate(const sf::Vector2f& position);
	};
}