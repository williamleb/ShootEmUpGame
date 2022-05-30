#pragma once
#include <SFML/System.hpp>
#include "IUpdatable.h"
#include <climits>

namespace TP3
{
	class GameScene;
	class Player;
	
	/// <summary>
	/// Représente une arme dans le jeu.
	/// </summary>
	/// <seealso cref="IUpdatable" />
	class Weapon : public IUpdatable
	{
	public:
		enum WeaponType
		{
			FORWARD_BLASTER,
			SIDE_BLASTER,
			TRI_SHOOTER,
			DOUBLE_BLASTER,
			SLASHER,
			TWISTED_SHOOTER
		};

	private:
		static GameScene* gameScene;
		static Player* player;
		

		const int fireRateInMS;
		const unsigned int maxAmmo;
		const unsigned int defaultAmmo;

		unsigned int ammo;

		sf::Time fireTimer;

		WeaponType type;

	public:
		static const unsigned int INFINITE_AMMO = UINT32_MAX;

		Weapon(const WeaponType type, const int fireRate, const unsigned int defaultAmmo, const unsigned int maxAmmo = UINT32_MAX);
		virtual ~Weapon();
		
		void update(const float deltaT);

		virtual void fire() = 0;

		static void setGameScene(GameScene* gameScene);
		static void setPlayer(Player* player);

		unsigned int getAmmo() const;
		bool empty() const;

		void addAmmo(const unsigned int ammo);
		void addDefaultAmmo();
		void loseAmmo(const unsigned int ammo = 1);

		WeaponType getType();

	protected:
		bool tryFire();

		static GameScene* getGameScene();
		static Player* getPlayer();
		
	};
}