#pragma once
#include "RessourceManager.h"
#include "EnemyProjectile.h"

namespace TP3
{
	/// <summary>
	/// Le Lazer est un projectile ennemi.
	/// C'est une ligne à l'horizontale qui suit toujours la même direction.
	/// </summary>
	/// <seealso cref="EnemyProjectile" />
	class Lazer : public EnemyProjectile
	{
		static const int LAZER_SPEED = 600;
		static const int LAZER_POWER = 1;
		static const int LAZER_HEALTH = 3;

		static const int LAZER_WIDTH = 80;
		static const int LAZER_HEIGHT = 12;

	public:
		Lazer();
		void init(RessourceManager::key spriteKey);
		
	};
}
