#pragma once

#include "Enemy.h"
#include "RessourceManager.h"

namespace TP3
{	
	/// <summary>
	/// Le Trooper est un ennemi qui suit plus ou moins le joueur (en zigzagant vaguement dans sa direction)
	/// en tentant de lui tirer dessus.
	/// </summary>
	/// <seealso cref="Enemy" />
	class Trooper : public Enemy
	{
	public:
		static const int TROOPER_DEFAULT_SPEED = 200;

	private:
		static const int TROOPER_FIRERATE = 750;
		static const int TROOPER_DEFAULT_LIFE = 3;
		static const int TROOPER_POINTS = 100;
		static const int TROOPER_COLLISION_DAMAGE = 5;

		static const float ROTATION_SPEED;

		static const float MAX_ANGLE;
		static const float MIN_ANGLE;

		float angle;
	public:
		static const int TROOPER_WIDTH = 128;
		static const int TROOPER_HEIGHT = 66;

		Trooper();
		virtual ~Trooper();

		virtual void update(const float deltaT);
		bool init(const RessourceManager::key spriteKey);

		virtual void fire();

		virtual void reset();

	protected:
		Trooper(const GameObject::ObjectType type);
	};
}