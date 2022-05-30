#pragma once

#include "Enemy.h"
#include "RessourceManager.h"

namespace TP3
{	
	/// <summary>
	/// Le Carrier est un ennemi qui se déplace en ligne droite. Il n'attaque pas et, lorsqu'il meurt, il
	/// lâche obligatoirement un bonus.
	/// </summary>
	/// <seealso cref="Enemy" />
	class Carrier : public Enemy
	{
		static const int CARRIER_DEFAULT_SPEED = 125;
		static const int CARRIER_FIRERATE = INT_MAX;
		static const int CARRIER_DEFAULT_LIFE = 30;
		static const int CARRIER_POINTS = 0;
		static const int CARRIER_COLLISION_DAMAGE = 100;

	public:
		static const int CARRIER_WIDTH = 128;
		static const int CARRIER_HEIGHT = 64;

		Carrier();

		void update(const float deltaT);
		bool init(const RessourceManager::key spriteKey);

		void fire();
	};
}