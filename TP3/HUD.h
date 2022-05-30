#pragma once

#include "GameObject.h"
#include "IObservateur.h"
#include "Shield.h"
#include "RessourceManager.h"
#include "IUpdatable.h"
#include "Weapon.h"
#include "Structures\list.h"

namespace TP3
{	
	/// <summary>
	/// Classe qui représente le HUD.
	/// Le HUD s'occupe du score et des armes.
	/// Il affiche également au joueur sa vie et les boucliers qu'il lui restent.
	/// </summary>
	/// <seealso cref="GameObject" />
	/// <seealso cref="IObservateur" />
	/// <seealso cref="IUpdatable" />
	class HUD : public GameObject, public IObservateur, public IUpdatable
	{
		// Affichage ---------------------------------------------------------
		static const int HUD_WIDTH = 1280;
		static const int HUD_HEIGHT = 300;

		RessourceManager::key multiplierSpriteKey;
		RessourceManager::key shieldSpriteKey;
		RessourceManager::key shieldTextKey;
		RessourceManager::key weaponTextKey;
		RessourceManager::key scoreTextKey;
		RessourceManager::key lifeTextKey;

		class WeaponBox;
		class ShieldBox;
		class Multiplier;

		static const int SCORE_POS_X = 240;
		static const int SCORE_POS_Y = 50;
		static const int NBR_CHARACTERS_IN_SCORE = 12;

		static const int LIFE_POS_X = 975;
		static const int LIFE_POS_Y = 25;

		static const int MULTIPLIER_POS_X = 55;
		static const int MULTIPLIER_POS_Y = 125;
		static const int MULTIPLIER_WIDTH = 100;
		static const int MULTIPLIER_HEIGHT = 50;
		sf::IntRect multiplierRect;

		static const int WEAPONBOX_LIST_POS_X = 0;
		static const int WEAPONBOX_LIST_POS_Y = 205;

		static const int SHIELD_BOX_POS_X = 1015;
		static const int SHIELD_BOX_POS_Y = 110;
		static const int SHIELD_BOX_NBR_SHIELD_X = 4;
		static const int SHIELD_BOX_NBR_SHIELD_Y = 3;

		// Logique -----------------------------------------------------------
		TP3_structures::list<ShieldBox*> allShieldBoxes;
		TP3_structures::list<WeaponBox*> allWeaponBoxes;

		TP3_structures::list<Multiplier*> allMultipliers;

		TP3_structures::list<WeaponBox*> weaponBoxesToDelete;

		unsigned int score;

		unsigned int playerLife;

		TP3_structures::list<WeaponBox*>::iterator currentWeapon;

	public:		
		HUD(const RessourceManager::key spriteKey, const RessourceManager::key shieldSpriteKey, const RessourceManager::key multiplierSpriteKey, const RessourceManager::key shieldTextKey, const RessourceManager::key weaponTextKey, const RessourceManager::key scoreTextKey, const RessourceManager::key lifeTextKey);
		~HUD();

		void draw(sf::RenderWindow& window);

		void update(const float deltaT);

		void notifier(Sujet* sujet);

		unsigned int getScore();

		void addWeapon(const Weapon::WeaponType type);
		void removeWeapon(const Weapon::WeaponType type);

		void selectLeftWeapon();
		void selectRightWeapon();

		Weapon* getCurrentWeapon() const;

		void setLife(const unsigned int life);
		void setLastShieldLife(const unsigned int life);

		void deleteUnusedWeapons();
	};
	
	/// <summary>
	/// Une WeaponBox contient une arme et l'information nécessaire pour s'afficher
	/// dans l'HUD.
	/// </summary>
	class HUD::WeaponBox
	{
	public:
		static const int WEAPONBOX_WIDTH = 200;
		static const int WEAPONBOX_HEIGHT = 50;

	private:
		static const sf::Color unselectedColor;
		static const sf::Color selectedColor;

		std::string weaponName;
		sf::RectangleShape shape;
		bool selected;
		RessourceManager::key weaponTextKey;
		Weapon* weapon;

	public:
		WeaponBox(Weapon* weapon, const std::string& weaponName, const RessourceManager::key weaponTextKey);

		void select();
		void unselect();
		bool isSelected() const;

		void draw(sf::RenderWindow& window, const sf::Vector2f& position);

		Weapon* getWeapon() const;

	};
	
	/// <summary>
	/// Un ShieldBox est la représentation d'un bouclier du joueur dans le HUD.
	/// </summary>
	class HUD::ShieldBox
	{
	public:
		static const int SHIELD_WIDTH = 50;
		static const int SHIELD_HEIGHT = 25;

	private:
		RessourceManager::key spriteKey;
		RessourceManager::key textKey;
		sf::Color color;
		unsigned int life;
		bool _first;

	public:
		ShieldBox(const RessourceManager::key spriteKey, const RessourceManager::key textKey, const sf::Color& color);

		void changeLife(const unsigned int life);

		void first();
		void unfirst();
		bool isFirst();

		void draw(sf::RenderWindow& window, const sf::Vector2f& position);

	};
	
	/// <summary>
	/// Un Multiplier est la représentation d'un multiplicateur de points.
	/// </summary>
	class HUD::Multiplier
	{
		int value;

		unsigned int lifeTime;

		sf::Time innerTimer;
	public:
		Multiplier(const unsigned int lifeTime, const int value = 2);

		bool update(const float deltaT);

		int getValue() const;

		const Multiplier operator*(const Multiplier& right);
		int operator*(const int right);
	};
}