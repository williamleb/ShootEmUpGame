#pragma once

#include "Enemy.h"
#include "FollowEntity.h"
#include "Trooper.h"

namespace TP3
{
	class Followed;
	
	/// <summary>
	/// Un Follower est un ennemi qui a seulement du sens lorsqu'il est attaché à un Followed.
	/// Il reproduit ses mouvement selon un certain décalage (il est souvent placé avec d'autre
	/// Follower, formant une file d'ennemis).
	/// </summary>
	/// <seealso cref="Enemy" />
	/// <seealso cref="FollowEntity" />
	class Follower : public Enemy, public FollowEntity
	{
		Followed* followed;

		static const int FOLLOWER_DEFAULT_SPEED = Trooper::TROOPER_DEFAULT_SPEED;
		static const int FOLLOWER_FIRERATE = INT_MAX;
		static const int FOLLOWER_DEFAULT_LIFE = 3;
		static const int FOLLOWER_POINTS = 85;
		static const int FOLLOWER_COLLISION_DAMAGE = 2;

		static const int MS_MOVING_DELAY = 500;

		int timeSinceSpawnedInMs;

		sf::Time innerTimer;
		sf::Int32 timeStartedInMs;
		sf::Time lastTimeShoot;
	public:
		static const int FOLLOWER_WIDTH = 75;
		static const int FOLLOWER_HEIGHT = 63;

		Follower();

		void update(const float deltaT);
		bool init(const RessourceManager::key spriteKey);

		void fire();
		void fireCommand();
		void changeDirection(const sf::Vector2f direction);

		void activate(Followed* followed);
		void deactivate();

	};
}