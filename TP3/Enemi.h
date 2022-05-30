#pragma once
#include "RessourceManager.h"
#include "Movable.h"
#include "Destroyable.h"
#include "Activatable.h"
#include"Player.h"
#include "Enemy.h"

using namespace sf;
namespace TP3
{
	class Enemi: public Enemy
	{
	private:
		Player *joueur;
		static const int ENEMI_DEFAULT_SPEED = 100;
		const int FIRE_RATE=1000;
		const int DEFAULT_LIFE=5;
		const int POINTS_GIVEN=100;
		const int COLLISION_DAMAGE=10;
		const int WIDTH = 16;
		const int HEIGHT = 34;
		Vector2f deplacement;
		bool top=false;
		// Mécanique de tir.
		static const int NBR_MS_BEFORE_SHOOT = 60;
		int shootTimerInMs=0;
	public:
		Enemi();
		~Enemi();
		void fire();
		void init(const RessourceManager::key spriteKey, Player *player);
		void update(const float deltaT);
		void draw(RenderWindow& window);
		void activate(const sf::Vector2f& position);
		virtual void getType();
		
	};
}
