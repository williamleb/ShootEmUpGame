#pragma once
#include "Projectile.h"

namespace TP3
{
	/// <summary>
	/// Cr�e un projectile alli� de type PlasmaBall.
	/// Le PlasmaBall est fait en rond et va en ligne droite.
	/// </summary>
	/// <seealso cref="Projectile" />
	class PlasmaBall : public Projectile
	{
	private:
		static const int PLASMA_BALL_SPEED = 400;
		static const int PLASMA_BALL_POWER = 1;
		static const int PLASMA_BALL_HEALTH = 3;

		static const int PLASMA_BALL_WIDTH = 32;
		static const int PLASMA_BALL_HEIGHT = 32;

	public:
		PlasmaBall();
		void init(RessourceManager::key spriteKey);
	};
}