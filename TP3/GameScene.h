#pragma once
#include "Scene.h"

#include "GameObject.h"
#include "IUpdatable.h"
#include "Destroyable.h"
#include "Activatable.h"
#include "Movable.h"
#include "Board.h"
#include "Weapon.h"
#include "Turret.h"
#include "ProjectileTurret.h"
#include "HUD.h"
#include "Followed.h"
#include "Player.h"
#include "Structures\list.h"
#include "Structures\deque.h"

namespace TP3
{	
	class Enemy;
	
	/// <summary>
	/// Scène du jeu.
	/// </summary>
	/// <seealso cref="Scene" />
	/// <seealso cref="IObservateur" />
	class GameScene : public Scene, public IObservateur
	{
	public:
		// Dimensions du jeu (pour l'instant, ce sont des valeurs temporaires).
		static const int GAME_WIDTH = 1280;
		static const int GAME_HEIGHT = 700;		

		// Position du coin supérieur droit de la fenêtre de jeu.
		static const int GAME_TOP = 300;
		static const int GAME_LEFT = 0;

		static const int SCROLLING_SPEED = 100;

		enum Ressource : RessourceManager::key
		{
			TEXTURE_PLAYER = 001,
			TEXTURE_ENEMI,
			TEXTURE_SHIELD,
			TEXTURE_OPTION,
			TEXTURE_LAZER,
			TEXTURE_ENERGY_BALL,
			TEXTURE_TURRET,
			TEXTURE_STALKER,
			TEXTURE_SHADOW,
			TEXTURE_TROOPER,
			TEXTURE_FOLLOWER,
			TEXTURE_CRUSHER,
			TEXTURE_CARRIER,
			TEXTURE_PROJECTILE_TURRET,
			TEXTURE_PROJECTILE_RED,
			TEXTURE_HUD,
			TEXTURE_HUD_MULTIPLIERS,
			TEXTURE_HUD_SHIELD,
			TEXTURE_BONUS_SHIELD,
			TEXTURE_BONUS_ELECTRO_BOMB,
			TEXTURE_BONUS_EXPLOSIVE_BOMB,
			TEXTURE_BONUS_OPTION,
			TEXTURE_BONUS_POINTS,
			TEXTURE_BONUS_WEAPON,
			TEXTURE_BEAM,
			TEXTURE_PLASMA_BALL,
			TEXTURE_SLASH,
			TEXTURE_TWIST,
			TEXTURE_CARGO,
			TEXTURE_BACKGROUND_LAYER1,
			TEXTURE_BACKGROUND_LAYER2,
			TEXTURE_BACKGROUND_LAYER3,
			TEXTURE_SPACE_GROUND,
			TEXTURE_CAVE_FLOOR_1,
			TEXTURE_CAVE_FLOOR_2,
			TEXTURE_CAVE_FLOOR_3,
			TEXTURE_CAVE_FLOOR_4,
			TEXTURE_CAVE_FLOOR_5,
			TEXTURE_CAVE_ROOF_1,
			TEXTURE_CAVE_ROOF_2,
			TEXTURE_CAVE_ROOF_3,
			TEXTURE_CAVE_ROOF_4,
			TEXTURE_CAVE_ROOF_5,
			TEXTURE_CAVE_WALL_1,
			TEXTURE_CAVE_WALL_2,
			TEXTURE_CAVE_WALL_3,
			TEXTURE_CAVE_WALL_4,
			TEXTURE_CAVE_WALL_5,
			TEXTURE_FACTORY_ENTRANCE_BOTTOM,
			TEXTURE_FACTORY_ENTRANCE_TOP,
			TEXTURE_FACTORY_ENTRANCE_WALL,
			TEXTURE_FACTORY_FLOOR,
			TEXTURE_FACTORY_OBSTACLE,
			TEXTURE_FACTORY_ROOF,
			TEXTURE_FACTORY_WALL,
			TEXTURE_FACTORY_WINDOW,
			TEXTURE_PIPE_BIG,
			TEXTURE_PIPE_SMALL,
			TEXTURE_SPACE_HILL_1,
			TEXTURE_SPACE_HILL_2,
			TEXTURE_SPACE_HILL_3,
			TEXTURE_SPACE_HILL_4,
			TEXTURE_SPACE_HILL_5,
			TEXTURE_SPACE_ROCK,

			SPRITE_PLAYER = 101,
			SPRITE_ENEMI,
			SPRITE_OPTION,
			SPRITE_SHIELD,
			SPRITE_LAZER,
			SPRITE_ENERGY_BALL,
			SPRITE_TURRET,
			SPRITE_STALKER,
			SPRITE_SHADOW,
			SPRITE_TROOPER,
			SPRITE_FOLLOWER,
			SPRITE_CRUSHER,
			SPRITE_CARRIER,
			SPRITE_PROJECTILE_RED,
			SPRITE_PROJECTILE_TURRET,
			SPRITE_HUD,
			SPRITE_HUD_MULTIPLIERS,
			SPRITE_HUD_SHIELD,
			SPRITE_BONUS_SHIELD,
			SPRITE_BONUS_ELECTRO_BOMB,
			SPRITE_BONUS_EXPLOSIVE_BOMB,
			SPRITE_BONUS_OPTION,
			SPRITE_BONUS_POINTS,
			SPRITE_BONUS_WEAPON,
			SPRITE_BEAM,
			SPRITE_PLASMA_BALL,
			SPRITE_SLASH,
			SPRITE_TWIST,
			SPRITE_CARGO,
			SPRITE_BACKGROUND_LAYER1,
			SPRITE_BACKGROUND_LAYER2,
			SPRITE_BACKGROUND_LAYER3,
			SPRITE_SPACE_GROUND,
			SPRITE_CAVE_FLOOR_1,
			SPRITE_CAVE_FLOOR_2,
			SPRITE_CAVE_FLOOR_3,
			SPRITE_CAVE_FLOOR_4,
			SPRITE_CAVE_FLOOR_5,
			SPRITE_CAVE_ROOF_1,
			SPRITE_CAVE_ROOF_2,
			SPRITE_CAVE_ROOF_3,
			SPRITE_CAVE_ROOF_4,
			SPRITE_CAVE_ROOF_5,
			SPRITE_CAVE_WALL_1,
			SPRITE_CAVE_WALL_2,
			SPRITE_CAVE_WALL_3,
			SPRITE_CAVE_WALL_4,
			SPRITE_CAVE_WALL_5,
			SPRITE_FACTORY_ENTRANCE_BOTTOM,
			SPRITE_FACTORY_ENTRANCE_TOP,
			SPRITE_FACTORY_ENTRANCE_WALL,
			SPRITE_FACTORY_FLOOR,
			SPRITE_FACTORY_OBSTACLE,
			SPRITE_FACTORY_ROOF,
			SPRITE_FACTORY_WALL,
			SPRITE_FACTORY_WINDOW,
			SPRITE_PIPE_BIG,
			SPRITE_PIPE_SMALL,
			SPRITE_SPACE_HILL_1,
			SPRITE_SPACE_HILL_2,
			SPRITE_SPACE_HILL_3,
			SPRITE_SPACE_HILL_4,
			SPRITE_SPACE_HILL_5,
			SPRITE_SPACE_ROCK,

			TEXT_SHIELD_LIFE = 201,
			TEXT_WEAPON_NAME,
			TEXT_SCORE,
			TEXT_LIFE,

			SOUND_MAIN_MENU=301,
			SOUND_BLASTER_FIRE,
			SOUND_EXPLO_BOMB
		};

		static const int SHIELD_LIFE_FONT_SIZE = 10;
		static const int WEAPON_NAME_FONT_SIZE = 30;
		static const int SCORE_FONT_SIZE = 92;
		static const int LIFE_FONT_SIZE = 45;

		sf::Color colors[3];

		GameScene();		
		~GameScene();
		
		scenes run();		
		bool init(sf::RenderWindow* const window);		
		void getInputs();		
		void update();		
		void draw();

		const sf::Time& getTimeSinceStart() const;
		const sf::Color& getGameColor(unsigned int index) const;

		void notifier(Sujet* sujet);

	private:		
		bool init_level();
		bool init_allTextures();
		void init_allSprites();
		bool init_allTexts();
		void init_allSubscriptions();
		void init_allObjects();
		bool init_allSounds();
		void update_level();
		void update_manageCollisions();

		unsigned int currentBoard;
		unsigned int nextBoard;

		bool gameCompleted;
		unsigned int scoreFinal;

		TP3_structures::deque<Board*> listOfBoards;

		RessourceManager* ressourceManager;

		sf::Time tempsDernierUpdate;

		sf::Clock timer;

		// Objets ------------------------------------------------------------
	private:
		// Le nombre total de GameObject chargés pour la scène.
		static const int NBR_OF_GAMEOBJECTS = 1000;
		static const int NBR_OF_DOUBLE_BLASTER_ADDERS = 1;
		static const int NBR_OF_SIDE_BLASTER_ADDERS = 1;
		static const int NBR_OF_SLASHER_ADDERS = 1;
		static const int NBR_OF_TRI_SHOOTER_ADDERS = 1;
		static const int NBR_OF_TWISTED_SHOOTER_ADDERS = 1;
		static const int NBR_OF_ELECTRO_BOMBS = 1;
		static const int NBR_OF_EXPLOSIVE_BOMBS = 1;
		static const int NBR_OF_OPTION_ADDERS = 1;
		static const int NBR_OF_POINTS_MULTIPLICATORS = 1;
		static const int NBR_OF_SHIELD_ADDERS = 4;
		static const int NBR_OF_FOLLOWED_CARGOS = 1;
		static const int NBR_OF_TROOPER_CARGOS = 2;
		static const int NBR_OF_FOLLOWEDS = 10;
		static const int NBR_OF_FOLLOWERS = 50;
		static const int NBR_OF_CARRIERS = 2;
		static const int NBR_OF_CRUSHERS = 8;
		static const int NBR_OF_SHADOWS = 4;
		static const int NBR_OF_STALKERS = 2;
		static const int NBR_OF_TROOPERS = 15;
		static const int NBR_OF_TURRETS = 20;
		static const int NBR_OF_ENERGY_BALLS = 15;
		static const int NBR_OF_LAZERS = 30;
		static const int NBR_OF_BEAMS = 75;
		static const int NBR_OF_PLASMA_BALLS = 75;
		static const int NBR_OF_SLASHES = 10;
		static const int NBR_OF_TWISTS = 50;
		static const int NBR_OF_PRIJECTILES_TURRET = 75;
		static const int NBR_OF_OPTIONS = 5;

		// Variables pour gérer la probabilité d'apparition des différents bonus.
		static const int POURCENTAGE_BONUS_SPAWN = 15;
		static const int THRESHOLD_DOUBLE_BLASTER_ADDER = 3;
		static const int THRESHOLD_SIDE_BLASTER_ADDER = 6;
		static const int THRESHOLD_SLASHER_ADDER = 9;
		static const int THRESHOLD_TRI_SHOOTER_ADDER = 12;
		static const int THRESHOLD_TWISTED_SHOOTER_ADDER = 15;
		static const int THRESHOLD_ELECTRO_BOMB = 25;
		static const int THRESHOLD_EXPLOSIVE_BOMB = 30;
		static const int THRESHOLD_OPTION_ADDER = 40;
		static const int THRESHOLD_POINTS_MULTIPLICATOR = 60;
		static const int THRESHOLD_SHIELD_ADDER = 100;

		sf::Font font;
		bool finDePartie = false;
		unsigned int nbrOfStalkerKilled;

		// Tous les objets du jeu sont contenus dans allGameObjects
		// Les structures allUpdatable, all Activatable et allDestroyable
		// contiennent des objets qui sont également dans allGameObject.
		// Elles sont utilisées pour éviter au maximum le casting.
		GameObject* allGameObjects[NBR_OF_GAMEOBJECTS];
		TP3_structures::list<IUpdatable*> allUpdatable;
		TP3_structures::list<Activatable*> allActivatable;
		TP3_structures::list<Destroyable*> allDestroyable;

		TP3_structures::list<IUpdatable*> updatablesToRemove;
		
		bool addObject(GameObject* object);

		HUD* hud;
		Player* player;

		static const int MS_OF_EXPLOSION = 100;
		sf::Time timerExplosion;
		sf::RectangleShape explosion;
		bool isExploding;

	public:	
		// Pour que le HUD puisse ajouter et retirer des armes.
		void addUpdatable(IUpdatable* updatable);
		void removeUpdatable(IUpdatable* updatable);

		// Pour la scène de fin
		unsigned int getScore();
		bool isCompleted();

		// Méthodes pour activer des objets.
		bool activateObject(const GameObject::ObjectType type, const sf::Vector2f& position);
		bool activateObject(const GameObject::ObjectType type, const float posX, const float posY);
		bool activateMovable(const GameObject::ObjectType type, const sf::Vector2f& position, const sf::Vector2f& direction);
		bool activateMovable(const GameObject::ObjectType type, const float posX, const float posY, const sf::Vector2f& direction);
		bool activateMovable(const GameObject::ObjectType type, const sf::Vector2f& position, const	Movable::Direction direction);
		bool activateMovable(const GameObject::ObjectType type, const float posX, const float posY, const Movable::Direction direction);
		bool activateMovable(const GameObject::ObjectType type, const sf::Vector2f& position, const	float angle);
		bool activateMovable(const GameObject::ObjectType type, const float posX, const float posY, const float angle);
		bool activateEnemyProjectile(const GameObject::ObjectType type, const Enemy* enemy, const sf::Vector2f& direction, const sf::Vector2f position = sf::Vector2f(0, 0));
		bool activateEnemyProjectile(const GameObject::ObjectType type, const Enemy* enemy, const	Movable::Direction direction, const sf::Vector2f position = sf::Vector2f(0, 0));
		bool activateEnemyProjectile(const GameObject::ObjectType type, const Enemy* enemy, const	float angle, const sf::Vector2f position = sf::Vector2f(0, 0));
		bool activateFollower(Followed* followed);		
		bool activateBonus(const sf::Vector2f& position);
	};
}