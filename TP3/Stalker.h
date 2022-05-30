#pragma once

#include "Enemy.h"
#include "RessourceManager.h"

namespace TP3
{	
	/// <summary>
	/// Le Stalker suit le joueur verticalement à la perfection jusqu'à ce qu'il meurt.
	/// Il arrête sa course au milieu de l'écran.
	/// </summary>
	/// <seealso cref="Enemy" />
	class Stalker : public Enemy
	{
		static const int STALKER_DEFAULT_SPEED = 75;
		static const int STALKER_FIRERATE = 3000;
		static const int STALKER_DEFAULT_LIFE = 20;
		static const int STALKER_POINTS = 500;
		static const int STALKER_COLLISION_DAMAGE = 20;

	public:
		static const int STALKER_WIDTH = 256;
		static const int STALKER_HEIGHT = 128;

		Stalker();

		void update(const float deltaT);
		bool init(const RessourceManager::key spriteKey);

		void fire();
	};
}