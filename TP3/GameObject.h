#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "RessourceManager.h"

namespace TP3
{

	class GameScene;

	/// <summary>
	/// Représente un objet de jeu qui peut être dessiné.
	/// </summary>
	class GameObject
	{
		static GameScene* gameScene;

	public:
		static void setGameScene(GameScene* gameScene);

		/// <summary>
		/// Un tag qui représente tous les objets concrets du jeu.
		/// </summary>
		enum ObjectType
		{
			PLAYER,
			OPTION,
			ENEMI,
			LAZER,
			ENERGY_BALL,
			RED_LAZER,
			TURRET,
			STALKER,
			SHADOW,
			TROOPER,
			FOLLOWED,
			FOLLOWER,
			CRUSHER,
			CARRIER,
			PROJECTILE_TURRET,
			BEAM,
			PLASMA_BALL,
			SLASH,
			TWIST,
			BOARD,
			BOARD_OBSTACLE,
			BACKGROUND,
			SHIELD_ADDER,
			ELECTRO_BOMB,
			EXPLOSIVE_BOMB,
			POINTS_MULTIPLICATOR,
			OPTION_ADDER,
			DOUBLE_BLASTER_ADDER,
			SIDE_BLASTER_ADDER,
			SLASHER_ADDER,
			TRI_SHOOTER_ADDER,
			TWISTED_SHOOTER_ADDER,
			HUD,
			TROOPER_CARGO,
			FOLLOWED_CARGO
		};

		ObjectType type;

	private:
		sf::Vector2f position;
		sf::Vector2f dimension;
		sf::IntRect collisionRect;

		RessourceManager::key spriteKey;

	public:		
		virtual ~GameObject();

		virtual void draw(sf::RenderWindow& window);

		virtual bool collidesWith(const GameObject& other) const;
		virtual bool contains(const sf::Vector2f& position) const;

		float getDistanceWith(const GameObject& other) const;
		float getDistanceWith(const sf::Vector2f& position) const;

		float getAngleWith(const GameObject& other) const;
		float getAngleWith(const sf::Vector2f& position) const;

		const sf::Vector2f& getPosition() const;
		const sf::Vector2f& getDimension() const;
		RessourceManager::key getSpriteKey() const;

		ObjectType getType() const;

		virtual void setPosition(const sf::Vector2f& position);
		virtual void setPosition(const float posX, const float posY);
		void setDimension(const sf::Vector2f& dimension);
		void setDimension(const float width, const float height);
		void setSpriteKey(const RessourceManager::key spriteKey);

	protected:
		GameObject(const ObjectType type);

		static GameScene* getGameScene();
	private:
		void computeCollisionRect();

		// Vérifications de type.
	public:
		bool isEnemy();
		static bool isEnemy(const ObjectType type);
		bool isProjectile();
		static bool isProjectile(const ObjectType type);
		bool isEnemyProjectile();
		static bool isEnemyProjectile(const ObjectType type);
		bool isBonus();
		static bool isBonus(const ObjectType type);
		bool isWeaponAdder();
		static bool isWeaponAdder(const ObjectType type);
		bool isCargo();
		static bool isCargo(const ObjectType type);
	};
}