#pragma once

#include "Enemy.h"

namespace TP3
{	
	/// <summary>
	/// Le Shadow est un ennmi qui sort de la droite de l'écran quelques instants, pour tirer,
	/// puis retourne là d'où il vient.
	/// </summary>
	/// <seealso cref="Enemy" />
	class Shadow : public Enemy
	{
		static const int SHADOW_MAX_SPEED = 400;
		static const int SHADOW_FIRERATE = 1000;
		static const int SHADOW_DEFAULT_LIFE = 5;
		static const int SHADOW_POINTS = 200;
		static const int SHADOW_COLLISION_DAMAGE = 5;

		static const int DECELERATION_VALUE = 300;

		static const float ACCURACY;

		static const int NBR_OF_FIRE_BEFORE_BACKING = 3;
		bool isFiring;
		bool hasFired;
		unsigned int nbrOfFire;

		static const float IDLE_THRESHOLD;
	public:
		static const int SHADOW_WIDTH = 90;
		static const int SHADOW_HEIGHT = 90;

		Shadow();

		void update(const float deltaT);
		bool init(const RessourceManager::key spriteKey);

		void fire();

		void reset();

	};
}