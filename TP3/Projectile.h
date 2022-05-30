#pragma once
#include "Movable.h"
#include "RessourceManager.h"
#include "Activatable.h"
#include "Destroyable.h"

namespace TP3
{	
	/// <summary>
	/// Représente un projectile dans le jeu.
	/// </summary>
	/// <seealso cref="Movable" />
	/// <seealso cref="Destroyable" />
	/// <seealso cref="Activatable" />
	class Projectile : public Movable, public Destroyable, public Activatable
	{
	public:		
		/// <summary>
		/// Représente les factions possibles pour le projectile.
		/// </summary>
		enum ProjectileFaction
		{
			PLAYER,
			ENEMY
		};
		enum Ressource : RessourceManager::key
		{
			SOUND_BLASTER_FIRE=302
		};

	private:
		ProjectileFaction faction;
		RessourceManager* ressourceManager;
		int power;


	protected:
		static const int PROJECTILE_DEFAULT_HEALTH = 3;

	public:		
		virtual ~Projectile();

		virtual void activate(const sf::Vector2f& position);

		void damage(const unsigned int life);

		ProjectileFaction getFaction() const;
		int getPower();


		virtual void update(const float deltaT);
		virtual void draw(sf::RenderWindow& window);

	protected:
		Projectile(const ObjectType type, const float speed, const int power = 1, const unsigned int health = PROJECTILE_DEFAULT_HEALTH, const ProjectileFaction faction = PLAYER);
		Projectile(const ObjectType type, const float speed, const int power = 1, const ProjectileFaction faction = PLAYER, const unsigned int health = PROJECTILE_DEFAULT_HEALTH);
	};
}