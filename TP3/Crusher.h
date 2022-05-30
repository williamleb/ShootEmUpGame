#pragma once

#include "Enemy.h"
#include "RessourceManager.h"

namespace TP3
{	
	/// <summary>
	/// Le Crusher est un ennemi qui tombe du haut de lécran jusqu'au bas de l'écran en tirant
	/// des projectiles au passage.
	/// </summary>
	/// <seealso cref="Enemy" />
	class Crusher : public Enemy
	{
		static const int CRUSHER_DEFAULT_SPEED = 75;
		static const int CRUSHER_FIRERATE = 750;
		static const int CRUSHER_DEFAULT_LIFE = 3;
		static const int CRUSHER_POINTS = 200;
		static const int CRUSHER_COLLISION_DAMAGE = 10;

		static const float ROTATION_SPEED;

		static const float MAX_ANGLE;
		static const float MIN_ANGLE;

		static const float ACCURACY;

		float angle;
		short balance;
	public:
		static const int CRUSHER_WIDTH = 112;
		static const int CRUSHER_HEIGHT = 40;

		Crusher();

		void update(const float deltaT);
		bool init(const RessourceManager::key spriteKey);

		void fire();

		void reset();
	};
}