#pragma once
#include "RessourceManager.h"
#include "Movable.h"
#include "Destroyable.h"
#include "Activatable.h"
#include "Player.h"
#define _USE_MATH_DEFINES 
#include <math.h>
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Enemy.h"

using namespace sf;
namespace TP3
{	
	/// <summary>
	/// La Turret est un ennemi qui vise le joueur et lui tire dessus tout en restant au même endroit.
	/// </summary>
	/// <seealso cref="Enemy" />
	class Turret : public Enemy
	{

		
	private:
		static const int ENEMI_DEFAULT_SPEED = 100;
		static const int FIRE_RATE = 1500;
		static const int DEFAULT_LIFE = 5;
		static const int POINTS_GIVEN = 100;
		static const int COLLISION_DAMAGE = 10;
		float angle=0;
		float angleCible;
		Weapon* currentWeapon;
		
		
	
	public:
		static const int TURRET_WIDTH = 113;
		static const int TURRET_HEIGHT = 53;

		Turret();
		~Turret();
		void fire();
		void init(const RessourceManager::key spriteKey);
		void findPlayer( const RessourceManager::key spriteKey);
		void update(const float deltaT);
		void draw(sf::RenderWindow& window);
		
	};
}

