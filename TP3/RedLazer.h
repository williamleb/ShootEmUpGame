#pragma once
#include "EnemyProjectile.h"
#include "RessourceManager.h"
namespace TP3
{
	class RedLazer : public EnemyProjectile
	{

	public:
		RedLazer();
		void init(RessourceManager::key spriteKey);
	private:
		static const int PROJECTILE_WIDTH = 8;
		static const int PROJECTILE_HEIGHT = 6;
		static const int SPEED = 500;
		


	};
}

