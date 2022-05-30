#include <cassert>
#include "GameScene.h"
#include "UserControlled.h"
#include "Movable.h"
#include "Background.h"
#include "BoardObstacle.h"
#include "Lazer.h"
#include "Player.h"
#include "Option.h"
#include "ProjectileTurret.h"
#include "EnemyProjectile.h"
#include "Beam.h"
#include "Slash.h"
#include "Twist.h"
#include "PlasmaBall.h"
#include "Enemy.h"
#include "HUD.h"
#include "ForwardBlaster.h"
#include "TwistedShooter.h"
#include "Slasher.h"
#include "DoubleBlaster.h"
#include "Weapon.h"
#include "Bonus.h"
#include "ShieldAdder.h"
#include "ElectroBomb.h"
#include "Stalker.h"
#include "Shadow.h"
#include "Trooper.h"
#include "Follower.h"
#include "Crusher.h"
#include "Carrier.h"
#include "TriShooter.h"
#include "EnergyBall.h"
#include "FollowedCargo.h"
#include "TrooperCargo.h"
#include "DoubleBlasterAdder.h"
#include "SideBlasterAdder.h"
#include "SlasherAdder.h"
#include "TriShooterAdder.h"
#include "TwistedShooterAdder.h"
#include "ExplosiveBomb.h"
#include "PointsMultiplicator.h"
#include "OptionAdder.h"


using namespace TP3;

/// <summary>
/// Crée une nouvelle <see cref="GameScene"/>.
/// </summary>
GameScene::GameScene()
	: timer(), tempsDernierUpdate(sf::microseconds(0))
{
	ressourceManager = RessourceManager::getInstance();
}

/// <summary>
/// Détruit la <see cref="GameScene"/>.
/// </summary>
GameScene::~GameScene()
{
	ressourceManager->clear();

	for (GameObject* object : allGameObjects)
	{
		if (object != nullptr)
		{
			delete object;
		}
	}
}

/// <summary>
/// Joue la scène de jeu.
/// </summary>
/// <returns>La prochaine scène à jouer. </returns>
Scene::scenes GameScene::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	scoreFinal = hud->getScore();

	if (gameCompleted)
	{
		while (player->getPosition().x - player->getDimension().x * 0.5f <= GAME_LEFT + GAME_WIDTH)
		{
			player->setPosition(player->getPosition().x + 500 * 0.0166667f, player->getPosition().y);
			draw();
		}

	}

	return transitionVersScene;
}

/// <summary>
/// Retourne le temps depuis le début du jeu.
/// </summary>
/// <returns>Le temps depuis le début du jeu.</returns>
const sf::Time& GameScene::getTimeSinceStart() const
{
	return timer.getElapsedTime();
}

/// <summary>
/// Renvoie l'une des couleurs utilisées dans le jeu.
/// </summary>
/// <param name="index">L'index de la couleur à renvoyer (1 à 3).</param>
/// <returns>La couleur demandée.</returns>
const sf::Color& GameScene::getGameColor(unsigned int index) const
{
	assert(index < 3 && "L'index de couleur doit être entre 0 et 2.");
	sf::Color color = colors[index];
	return colors[index];
}

/// <summary>
/// Initialise la scène de jeu.
/// </summary>
/// <param name="window">Le fenêtre utilisée par la scène de jeu.</param>
/// <returns>true si la scène s'est initialisée correctement; false sinon.</returns>
bool GameScene::init(RenderWindow * const window)
{
	colors[0] = sf::Color(rand() % 255, rand() % 255, rand() % 255);
	colors[1] = sf::Color(rand() % 255, rand() % 255, rand() % 255);
	colors[2] = sf::Color(rand() % 255, rand() % 255, rand() % 255);

	GameObject::setGameScene(this);
	Weapon::setGameScene(this);

	// On initialise le tableau des objets.
	for (unsigned int i = 0; i < NBR_OF_GAMEOBJECTS; i++)
	{
		allGameObjects[i] = nullptr;
	}

	if (!init_allTexts())
	{
		return false;
	}

	if (!init_allTextures())
	{
		return false;
	}

	init_allSprites();

	if (!init_level())
	{
		return false;
	}
	init_allSounds();

	init_allObjects();

	// Initialisation de la méchanique de déplacement du niveau.
	listOfBoards[0]->activate(sf::Vector2f(GAME_LEFT, 0) + (listOfBoards[0]->getDimension() * 0.5f));
	listOfBoards[1]->activate(sf::Vector2f(GAME_LEFT + Board::BOARD_WIDTH, 0) + (listOfBoards[0]->getDimension() * 0.5f));
	currentBoard = 0;
	nextBoard = 1;

	Weapon::setPlayer(player);
	Enemy::setPlayer(player);
	BoardObstacle::setPlayerTextureKey(TEXTURE_PLAYER);

	hud->addWeapon(Weapon::WeaponType::FORWARD_BLASTER);
	hud->addWeapon(Weapon::WeaponType::SIDE_BLASTER);

	player->changeWeapon(hud->getCurrentWeapon());

	init_allSubscriptions();

	mainWin = window;
	tempsDernierUpdate = sf::microseconds(0);
	timer.restart();
	gameCompleted = false;
	nbrOfStalkerKilled = 0;

	isExploding = false;
	timerExplosion = sf::microseconds(0);
	explosion.setPosition(GAME_LEFT, GAME_TOP);
	explosion.setSize(sf::Vector2f(GAME_WIDTH, GAME_HEIGHT));

	return true;
}

void GameScene::init_allObjects()
{
	// Le joueur.
	hud = new HUD(SPRITE_HUD, SPRITE_HUD_SHIELD, SPRITE_HUD_MULTIPLIERS, TEXT_SHIELD_LIFE, TEXT_WEAPON_NAME, TEXT_SCORE, TEXT_LIFE);
	hud->setPosition(0, 0);
	addObject(hud);

	// Le HUD.
	player = new Player();
	player->init(SPRITE_PLAYER, SPRITE_SHIELD);
	addObject(player);
	player->setPosition(100, 100);

	// Les bonus.
	DoubleBlasterAdder* doubleBlasterAdder = nullptr;
	for (size_t i = 0; i < NBR_OF_DOUBLE_BLASTER_ADDERS; i++)
	{
		doubleBlasterAdder = new DoubleBlasterAdder();
		doubleBlasterAdder->init(SPRITE_BONUS_WEAPON);
		addObject(doubleBlasterAdder);
	}

	SideBlasterAdder* sideBlasterAdder = nullptr;
	for (size_t i = 0; i < NBR_OF_SIDE_BLASTER_ADDERS; i++)
	{
		sideBlasterAdder = new SideBlasterAdder();
		sideBlasterAdder->init(SPRITE_BONUS_WEAPON);
		addObject(sideBlasterAdder);
	}

	SlasherAdder* slasherAdder = nullptr;
	for (size_t i = 0; i < NBR_OF_SLASHER_ADDERS; i++)
	{
		slasherAdder = new SlasherAdder();
		slasherAdder->init(SPRITE_BONUS_WEAPON);
		addObject(slasherAdder);
	}

	TriShooterAdder* triShooterAdder = nullptr;
	for (size_t i = 0; i < NBR_OF_TRI_SHOOTER_ADDERS; i++)
	{
		triShooterAdder = new TriShooterAdder();
		triShooterAdder->init(SPRITE_BONUS_WEAPON);
		addObject(triShooterAdder);
	}

	TwistedShooterAdder* twistedShooterAdder = nullptr;
	for (size_t i = 0; i < NBR_OF_TWISTED_SHOOTER_ADDERS; i++)
	{
		twistedShooterAdder = new TwistedShooterAdder();
		twistedShooterAdder->init(SPRITE_BONUS_WEAPON);
		addObject(twistedShooterAdder);
	}

	ElectroBomb* electroBomb = nullptr;
	for (size_t i = 0; i < NBR_OF_ELECTRO_BOMBS; i++)
	{
		electroBomb = new ElectroBomb();
		electroBomb->init(SPRITE_BONUS_ELECTRO_BOMB);
		addObject(electroBomb);
	}

	ShieldAdder* shieldAdder = nullptr;
	for (size_t i = 0; i < NBR_OF_SHIELD_ADDERS; i++)
	{
		shieldAdder = new ShieldAdder();
		shieldAdder->init(SPRITE_BONUS_SHIELD);
		addObject(shieldAdder);
	}

	ExplosiveBomb* explosiveBomb = nullptr;
	for (size_t i = 0; i < NBR_OF_EXPLOSIVE_BOMBS; i++)
	{
		explosiveBomb = new ExplosiveBomb();
		explosiveBomb->init(SPRITE_BONUS_EXPLOSIVE_BOMB);
		addObject(explosiveBomb);
	}

	OptionAdder* optionAdder = nullptr;
	for (size_t i = 0; i < NBR_OF_OPTION_ADDERS; i++)
	{
		optionAdder = new OptionAdder();
		optionAdder->init(SPRITE_BONUS_OPTION);
		addObject(optionAdder);
	}

	PointsMultiplicator* pointsMultiplicator = nullptr;
	for (size_t i = 0; i < NBR_OF_POINTS_MULTIPLICATORS; i++)
	{
		pointsMultiplicator = new PointsMultiplicator();
		pointsMultiplicator->init(SPRITE_BONUS_POINTS);
		addObject(pointsMultiplicator);
	}

	// Les cargos.
	FollowedCargo* followedCargo = nullptr;
	for (size_t i = 0; i < NBR_OF_FOLLOWED_CARGOS; i++)
	{
		followedCargo = new FollowedCargo();
		followedCargo->init(SPRITE_CARGO);
		addObject(followedCargo);
	}

	TrooperCargo* trooperCargo = nullptr;
	for (size_t i = 0; i < NBR_OF_TROOPER_CARGOS; i++)
	{
		trooperCargo = new TrooperCargo();
		trooperCargo->init(SPRITE_CARGO);
		addObject(trooperCargo);
	}

	// Les ennemis.
	Followed* followed = nullptr;
	for (size_t i = 0; i < NBR_OF_FOLLOWEDS; i++)
	{
		followed = new Followed();
		addObject(followed);
	}

	Follower* follower = nullptr;
	for (size_t i = 0; i < NBR_OF_FOLLOWERS; i++)
	{
		follower = new Follower();
		follower->init(SPRITE_FOLLOWER);
		addObject(follower);
	}

	Carrier* carrier = nullptr;
	for (size_t i = 0; i < NBR_OF_CARRIERS; i++)
	{
		carrier = new Carrier();
		carrier->init(SPRITE_CARRIER);
		addObject(carrier);
	}

	Crusher* crusher = nullptr;
	for (size_t i = 0; i < NBR_OF_CRUSHERS; i++)
	{
		crusher = new Crusher();
		crusher->init(SPRITE_CRUSHER);
		addObject(crusher);
	}

	Shadow* shadow = nullptr;
	for (size_t i = 0; i < NBR_OF_SHADOWS; i++)
	{
		shadow = new Shadow();
		shadow->init(SPRITE_SHADOW);
		addObject(shadow);
	}

	Stalker* stalker = nullptr;
	for (size_t i = 0; i < NBR_OF_STALKERS; i++)
	{
		stalker = new Stalker();
		stalker->init(SPRITE_STALKER);
		addObject(stalker);
	}

	Trooper* trooper = nullptr;
	for (size_t i = 0; i < NBR_OF_TROOPERS; i++)
	{
		trooper = new Trooper();
		trooper->init(SPRITE_TROOPER);
		addObject(trooper);
	}

	Turret* turret = nullptr;
	for (size_t i = 0; i < NBR_OF_TURRETS; i++)
	{
		turret = new Turret();
		turret->init(SPRITE_TURRET);
		addObject(turret);
	}

	// Les projectiles.
	EnergyBall* energyBall = nullptr;
	for (size_t i = 0; i < NBR_OF_ENERGY_BALLS; i++)
	{
		energyBall = new EnergyBall();
		energyBall->init(SPRITE_ENERGY_BALL);
		addObject(energyBall);
	}

	Lazer* lazer = nullptr;
	for (size_t i = 0; i < NBR_OF_LAZERS; i++)
	{
		lazer = new Lazer();
		lazer->init(SPRITE_LAZER);
		addObject(lazer);
	}

	Beam* beam = nullptr;
	for (size_t i = 0; i < NBR_OF_BEAMS; i++)
	{
		beam = new Beam();
		beam->init(SPRITE_BEAM);
		addObject(beam);
	}

	PlasmaBall* plasmaBall = nullptr;
	for (size_t i = 0; i < NBR_OF_PLASMA_BALLS; i++)
	{
		plasmaBall = new PlasmaBall();
		plasmaBall->init(SPRITE_PLASMA_BALL);
		addObject(plasmaBall);
	}

	Slash* slash = nullptr;
	for (size_t i = 0; i < NBR_OF_SLASHES; i++)
	{
		slash = new Slash();
		slash->init(SPRITE_SLASH);
		addObject(slash);
	}

	Twist* twist = nullptr;
	for (size_t i = 0; i < NBR_OF_TWISTS; i++)
	{
		twist = new Twist();
		twist->init(SPRITE_TWIST);
		addObject(twist);
	}

	ProjectileTurret* projectileTurret = nullptr;
	for (size_t i = 0; i < NBR_OF_TWISTS; i++)
	{
		projectileTurret = new ProjectileTurret();
		projectileTurret->init(SPRITE_PROJECTILE_TURRET);
		addObject(projectileTurret);
	}

	// Les options.
	Option* option = nullptr;
	for (size_t i = 0; i < NBR_OF_OPTIONS; i++)
	{
		option = new Option();
		option->init(SPRITE_OPTION, player);
		addObject(option);
	}

}

/// <summary>
/// Initialise tous les sons.
/// </summary>
/// <returns>true si tous les sons ont pu s'initialiser correctement; false sinon.</returns>
bool GameScene::init_allSounds()
{
	
	if (!ressourceManager->addMusic("Ressources\\Sounds\\blaster-firing.wav", SOUND_BLASTER_FIRE))
	{
		return false;
	}
	if (!ressourceManager->addMusic("Ressources\\Sounds\\ExploBomb.wav", SOUND_EXPLO_BOMB))
	{
		return false;
	}

	
}

/// <summary>
/// Crée et initalise le niveau.
/// </summary>
/// <returns>true si le niveau a pu s'initialiser correctement; false sinon.</returns>
bool GameScene::init_level()
{
	// Ajoute le background ------------------------------------------------
	addObject(new Background(3, 1, SPRITE_BACKGROUND_LAYER3));
	addObject(new Background(3, 2, SPRITE_BACKGROUND_LAYER3));
	addObject(new Background(2, 1, SPRITE_BACKGROUND_LAYER2));
	addObject(new Background(2, 2, SPRITE_BACKGROUND_LAYER2));
	addObject(new Background(1, 1, SPRITE_BACKGROUND_LAYER1));
	addObject(new Background(1, 2, SPRITE_BACKGROUND_LAYER1));

	// Construit le niveau -------------------------------------------------
	Board* constructedBoard = nullptr;
	BoardObstacle* constructedObstacle = nullptr;
	Board::EnemyPlacement* constructedEnemy = nullptr;

	// Board 1:
	constructedBoard = new Board(0);

	constructedObstacle = new BoardObstacle(1400, 60, SPRITE_SPACE_GROUND, TEXTURE_SPACE_GROUND);
	constructedObstacle->addCollisionBox(0, 0, 1400, 60);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 640) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1207, 90) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 2:
	constructedBoard = new Board(0);

	constructedObstacle = new BoardObstacle(1400, 60, SPRITE_SPACE_GROUND, TEXTURE_SPACE_GROUND);
	constructedObstacle->addCollisionBox(0, 0, 1400, 60);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 640) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(167, 480) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(809, 480) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(809, 72) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1183, 300) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(544, 303) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 3:
	constructedBoard = new Board(0);

	constructedObstacle = new BoardObstacle(1400, 60, SPRITE_SPACE_GROUND, TEXTURE_SPACE_GROUND);
	constructedObstacle->addCollisionBox(0, 0, 1400, 60);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 640) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(240, 55) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(240, 225) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(727, 364) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(727, 542) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1192, 111) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);


	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 4:
	constructedBoard = new Board(0);

	constructedObstacle = new BoardObstacle(1400, 60, SPRITE_SPACE_GROUND, TEXTURE_SPACE_GROUND);
	constructedObstacle->addCollisionBox(0, 0, 1400, 60);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 640) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(785, 712) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(215, 103) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(597, 277) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1089, 113) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CARRIER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(478, 517) + sf::Vector2f(Carrier::CARRIER_WIDTH, Carrier::CARRIER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 5:
	constructedBoard = new Board(0);

	constructedObstacle = new BoardObstacle(256, 384, SPRITE_SPACE_ROCK, TEXTURE_SPACE_ROCK);
	constructedObstacle->addCollisionBox(0, 0, 256, 384);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(482, 316) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1400, 60, SPRITE_SPACE_GROUND, TEXTURE_SPACE_GROUND);
	constructedObstacle->addCollisionBox(0, 0, 1400, 60);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 640) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(157, 28) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(439, 109) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(745, 199) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1183, 386) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(656, 300) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 6:
	constructedBoard = new Board(0);

	constructedObstacle = new BoardObstacle(384, 388, SPRITE_PIPE_SMALL, TEXTURE_PIPE_SMALL);
	constructedObstacle->addCollisionBox(0, 334, 384, 54);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(259, 0) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1400, 60, SPRITE_SPACE_GROUND, TEXTURE_SPACE_GROUND);
	constructedObstacle->addCollisionBox(0, 0, 1400, 60);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 640) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(91, 48, SPRITE_SPACE_HILL_1, TEXTURE_SPACE_HILL_1);
	constructedObstacle->addCollisionBox(0, 0, 91, 48);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1309, 652) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(178, 532) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(526, 532) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(962, 367) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(558, 161) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(203, 330) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(524, 362) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 7:
	constructedBoard = new Board(0);

	constructedObstacle = new BoardObstacle(256, 384, SPRITE_SPACE_ROCK, TEXTURE_SPACE_ROCK);
	constructedObstacle->addCollisionBox(0, 0, 256, 384);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(817, 316) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1400, 314, SPRITE_SPACE_HILL_2, TEXTURE_SPACE_HILL_2);
	constructedObstacle->addCollisionBox(0, 174, 310, 140);
	constructedObstacle->addCollisionBox(309, 51, 1091, 263);
	constructedObstacle->addCollisionBox(541, 0, 362, 314);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 386) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CARRIER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(652, 314) + sf::Vector2f(Carrier::CARRIER_WIDTH, Carrier::CARRIER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(159, 59) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER_CARGO, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(815, 197) + sf::Vector2f(Cargo::CARGO_WIDTH, Cargo::CARGO_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 8:
	constructedBoard = new Board(0);

	constructedObstacle = new BoardObstacle(384, 388, SPRITE_PIPE_SMALL, TEXTURE_PIPE_SMALL);
	constructedObstacle->addCollisionBox(0, 334, 384, 54);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(196, -150) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(384, 388, SPRITE_PIPE_SMALL, TEXTURE_PIPE_SMALL);
	constructedObstacle->addCollisionBox(0, 334, 384, 54);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(734, -150) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1400, 268, SPRITE_SPACE_HILL_3, TEXTURE_SPACE_HILL_3);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 431) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(347, 328) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(842, 319) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(221, 156) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(524, 186) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1020, 159) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(818, 213) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 9:
	constructedBoard = new Board(SPRITE_CAVE_WALL_1);

	constructedObstacle = new BoardObstacle(89, 196, SPRITE_SPACE_HILL_4, TEXTURE_SPACE_HILL_4);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 501) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1036, 562, SPRITE_CAVE_ROOF_1, TEXTURE_CAVE_ROOF_1);
	constructedObstacle->addCollisionBox(296, 0, 444, 238);
	constructedObstacle->addCollisionBox(740, 0, 296, 170);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(364, 0) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1217, 494, SPRITE_CAVE_FLOOR_1, TEXTURE_CAVE_FLOOR_1);
	constructedObstacle->addCollisionBox(189, 327, 477, 167);
	constructedObstacle->addCollisionBox(666, 359, 551, 135);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(183, 207) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CRUSHER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(46, 66) + sf::Vector2f(Crusher::CRUSHER_WIDTH, Crusher::CRUSHER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CRUSHER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(192, 22) + sf::Vector2f(Crusher::CRUSHER_WIDTH, Crusher::CRUSHER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(833, 358) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 10:
	constructedBoard = new Board(SPRITE_CAVE_WALL_2);

	constructedObstacle = new BoardObstacle(1401, 722, SPRITE_CAVE_ROOF_2, TEXTURE_CAVE_ROOF_2);
	constructedObstacle->addCollisionBox(0, 0, 1400, 170);
	constructedObstacle->addCollisionBox(1281, 0, 120, 258);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 0) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1400, 440, SPRITE_CAVE_FLOOR_2, TEXTURE_CAVE_FLOOR_2);
	constructedObstacle->addCollisionBox(0, 331, 1400, 109);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 261) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(69, 254));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(75, 424));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER_CARGO, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(788, 100) + sf::Vector2f(Cargo::CARGO_WIDTH, Cargo::CARGO_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 11:
	constructedBoard = new Board(SPRITE_CAVE_WALL_3);

	constructedObstacle = new BoardObstacle(1400, 757, SPRITE_CAVE_ROOF_3, TEXTURE_CAVE_ROOF_3);
	constructedObstacle->addCollisionBox(0, 0, 275, 462);
	constructedObstacle->addCollisionBox(275, 0, 780, 231);
	constructedObstacle->addCollisionBox(1055, 0, 345, 372);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 0) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1400, 697, SPRITE_CAVE_FLOOR_3, TEXTURE_CAVE_FLOOR_3);
	constructedObstacle->addCollisionBox(0, 614, 1400, 83);
	constructedObstacle->addCollisionBox(410, 509, 584, 188);
	constructedObstacle->addCollisionBox(517, 309, 353, 388);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 4) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CRUSHER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(321, 354) + sf::Vector2f(Crusher::CRUSHER_WIDTH, Crusher::CRUSHER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CRUSHER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(658, 177) + sf::Vector2f(Crusher::CRUSHER_WIDTH, Crusher::CRUSHER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CRUSHER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(930, 369) + sf::Vector2f(Crusher::CRUSHER_WIDTH, Crusher::CRUSHER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 12:
	constructedBoard = new Board(SPRITE_CAVE_WALL_4);

	constructedObstacle = new BoardObstacle(1400, 622, SPRITE_CAVE_ROOF_4, TEXTURE_CAVE_ROOF_4);
	constructedObstacle->addCollisionBox(0, 0, 1400, 157);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 0) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1400, 456, SPRITE_CAVE_FLOOR_4, TEXTURE_CAVE_FLOOR_4);
	constructedObstacle->addCollisionBox(0, 332, 1400, 124);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 244) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::STALKER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(366, 376) + sf::Vector2f(Stalker::STALKER_WIDTH, Stalker::STALKER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 13:
	constructedBoard = new Board(SPRITE_CAVE_WALL_5);

	constructedObstacle = new BoardObstacle(1400, 60, SPRITE_SPACE_GROUND, TEXTURE_SPACE_GROUND);
	constructedObstacle->addCollisionBox(0, 0, 1400, 60);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 640) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1413, 648, SPRITE_CAVE_ROOF_5, TEXTURE_CAVE_ROOF_5);
	constructedObstacle->addCollisionBox(0, 0, 294, 144);
	constructedObstacle->addCollisionBox(294, 0, 834, 332);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 0) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(865, 472, SPRITE_CAVE_FLOOR_5, TEXTURE_CAVE_FLOOR_5);
	constructedObstacle->addCollisionBox(0, 320, 599, 152);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 228) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1207, 720) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::FOLLOWED, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(687, 507) + sf::Vector2f(Follower::FOLLOWER_WIDTH, Follower::FOLLOWER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 14:
	constructedBoard = new Board(0);

	constructedObstacle = new BoardObstacle(928, 260, SPRITE_SPACE_HILL_5, TEXTURE_SPACE_HILL_5);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(234, 440) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1400, 60, SPRITE_SPACE_GROUND, TEXTURE_SPACE_GROUND);
	constructedObstacle->addCollisionBox(0, 0, 1400, 60);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 640) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(399, 116) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(403, 272) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(987, 109) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(991, 286) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(650, 419) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 15:
	constructedBoard = new Board(0);

	constructedObstacle = new BoardObstacle(768, 388, SPRITE_PIPE_BIG, TEXTURE_PIPE_BIG);
	constructedObstacle->addCollisionBox(0, 334, 768, 54);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(417, 0) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1400, 60, SPRITE_SPACE_GROUND, TEXTURE_SPACE_GROUND);
	constructedObstacle->addCollisionBox(0, 0, 1400, 60);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 640) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CARRIER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1044, 87) + sf::Vector2f(Carrier::CARRIER_WIDTH, Carrier::CARRIER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::FOLLOWED, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(573, 494) + sf::Vector2f(Follower::FOLLOWER_WIDTH, Follower::FOLLOWER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::FOLLOWED, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1002, 531) + sf::Vector2f(Follower::FOLLOWER_WIDTH, Follower::FOLLOWER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(406, 306) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(787, 307) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1072, 308) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 16:
	constructedBoard = new Board(0);

	constructedObstacle = new BoardObstacle(768, 388, SPRITE_PIPE_BIG, TEXTURE_PIPE_BIG);
	constructedObstacle->addCollisionBox(0, 334, 768, 54);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(305, 0) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1400, 60, SPRITE_SPACE_GROUND, TEXTURE_SPACE_GROUND);
	constructedObstacle->addCollisionBox(0, 0, 1400, 60);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 640) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(407, 451) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(608, 554) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(517, 111) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(525, 244) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(279, 142) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(883, 137) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(894, 511) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(365, 307) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(532, 361) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(841, 307) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 17:
	constructedBoard = new Board(0);

	constructedObstacle = new BoardObstacle(1400, 60, SPRITE_SPACE_GROUND, TEXTURE_SPACE_GROUND);
	constructedObstacle->addCollisionBox(0, 0, 1400, 60);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 640) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CARRIER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1245, 43) + sf::Vector2f(Carrier::CARRIER_WIDTH, Carrier::CARRIER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CRUSHER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(68, 39) + sf::Vector2f(Crusher::CRUSHER_WIDTH, Crusher::CRUSHER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CRUSHER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(200, 112) + sf::Vector2f(Crusher::CRUSHER_WIDTH, Crusher::CRUSHER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER_CARGO, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(432, 536) + sf::Vector2f(Cargo::CARGO_WIDTH, Cargo::CARGO_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER_CARGO, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(983, 535) + sf::Vector2f(Cargo::CARGO_WIDTH, Cargo::CARGO_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 18:
	constructedBoard = new Board(SPRITE_FACTORY_ENTRANCE_WALL);

	constructedObstacle = new BoardObstacle(1400, 60, SPRITE_SPACE_GROUND, TEXTURE_SPACE_GROUND);
	constructedObstacle->addCollisionBox(0, 0, 1400, 60);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 640) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(700, 175, SPRITE_FACTORY_ENTRANCE_TOP, TEXTURE_FACTORY_ENTRANCE_TOP);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(700, 0) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(700, 175, SPRITE_FACTORY_ENTRANCE_BOTTOM, TEXTURE_FACTORY_ENTRANCE_BOTTOM);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(700, 525) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1007, 495) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(998, 155) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1271, 155) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1280, 495) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 19:
	constructedBoard = new Board(SPRITE_FACTORY_WALL);

	constructedObstacle = new BoardObstacle(1400, 54, SPRITE_FACTORY_ROOF, TEXTURE_FACTORY_ROOF);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 0) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CRUSHER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(108, 116) + sf::Vector2f(Crusher::CRUSHER_WIDTH, Crusher::CRUSHER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CRUSHER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(113, 245) + sf::Vector2f(Crusher::CRUSHER_WIDTH, Crusher::CRUSHER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CRUSHER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(364, 167) + sf::Vector2f(Crusher::CRUSHER_WIDTH, Crusher::CRUSHER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CRUSHER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(538, 103) + sf::Vector2f(Crusher::CRUSHER_WIDTH, Crusher::CRUSHER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CRUSHER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(757, 208) + sf::Vector2f(Crusher::CRUSHER_WIDTH, Crusher::CRUSHER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CRUSHER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(946, 128) + sf::Vector2f(Crusher::CRUSHER_WIDTH, Crusher::CRUSHER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CRUSHER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1154, 144) + sf::Vector2f(Crusher::CRUSHER_WIDTH, Crusher::CRUSHER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(-55, 625) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 20:
	constructedBoard = new Board(SPRITE_FACTORY_WALL);

	constructedObstacle = new BoardObstacle(1400, 54, SPRITE_FACTORY_ROOF, TEXTURE_FACTORY_ROOF);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 0) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1400, 54, SPRITE_FACTORY_FLOOR, TEXTURE_FACTORY_FLOOR);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 646) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(700, 74, SPRITE_FACTORY_OBSTACLE, TEXTURE_FACTORY_OBSTACLE);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(647, 329) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::FOLLOWED, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(237, 473) + sf::Vector2f(Follower::FOLLOWER_WIDTH, Follower::FOLLOWER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::FOLLOWED, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(769, 515) + sf::Vector2f(Follower::FOLLOWER_WIDTH, Follower::FOLLOWER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(378, 141) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(735, 134) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1146, 134) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1269, 498) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(931, 301) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(766, 380) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 21:
	constructedBoard = new Board(SPRITE_FACTORY_WALL);

	constructedObstacle = new BoardObstacle(1400, 54, SPRITE_FACTORY_ROOF, TEXTURE_FACTORY_ROOF);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 0) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1400, 54, SPRITE_FACTORY_FLOOR, TEXTURE_FACTORY_FLOOR);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 646) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(700, 74, SPRITE_FACTORY_OBSTACLE, TEXTURE_FACTORY_OBSTACLE);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(320, 206) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(700, 74, SPRITE_FACTORY_OBSTACLE, TEXTURE_FACTORY_OBSTACLE);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(320, 443) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(497, 331) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(773, 334) + sf::Vector2f(Trooper::TROOPER_WIDTH, Trooper::TROOPER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::FOLLOWED, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(120, 346) + sf::Vector2f(Follower::FOLLOWER_WIDTH, Follower::FOLLOWER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::FOLLOWED, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1263, 366) + sf::Vector2f(Follower::FOLLOWER_WIDTH, Follower::FOLLOWER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(396, 540) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::SHADOW, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(828, 87) + sf::Vector2f(Shadow::SHADOW_WIDTH, Shadow::SHADOW_WIDTH * 0.5f));
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(629, 178) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(767, 491) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 22:
	constructedBoard = new Board(SPRITE_FACTORY_WINDOW);

	constructedObstacle = new BoardObstacle(1400, 54, SPRITE_FACTORY_ROOF, TEXTURE_FACTORY_ROOF);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 0) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1400, 54, SPRITE_FACTORY_FLOOR, TEXTURE_FACTORY_FLOOR);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 646) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::CARRIER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1091, 487) + sf::Vector2f(Carrier::CARRIER_WIDTH, Carrier::CARRIER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(200, 36) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(914, 617) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TROOPER_CARGO, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(213, 527) + sf::Vector2f(Cargo::CARGO_WIDTH, Cargo::CARGO_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::FOLLOWED_CARGO, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(983, 45) + sf::Vector2f(Cargo::CARGO_WIDTH, Cargo::CARGO_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 23:
	constructedBoard = new Board(SPRITE_FACTORY_WALL);

	constructedObstacle = new BoardObstacle(1400, 54, SPRITE_FACTORY_ROOF, TEXTURE_FACTORY_ROOF);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 0) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1400, 54, SPRITE_FACTORY_FLOOR, TEXTURE_FACTORY_FLOOR);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 646) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::STALKER, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(366, 376) + sf::Vector2f(Stalker::STALKER_WIDTH, Stalker::STALKER_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(74, 28) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(266, 28) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1060, 28) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(182, 615) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(928, 615) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 24:
	constructedBoard = new Board(SPRITE_FACTORY_WALL);

	constructedObstacle = new BoardObstacle(1400, 54, SPRITE_FACTORY_ROOF, TEXTURE_FACTORY_ROOF);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 0) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1400, 54, SPRITE_FACTORY_FLOOR, TEXTURE_FACTORY_FLOOR);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 646) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1204, 28) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(638, 28) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(354, 615) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(602, 615) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1144, 615) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	// Board 25:
	constructedBoard = new Board(SPRITE_FACTORY_WALL);

	constructedObstacle = new BoardObstacle(1400, 54, SPRITE_FACTORY_ROOF, TEXTURE_FACTORY_ROOF);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 0) + constructedObstacle->getDimension() * 0.5f);

	constructedObstacle = new BoardObstacle(1400, 54, SPRITE_FACTORY_FLOOR, TEXTURE_FACTORY_FLOOR);
	constructedBoard->addObstacle(constructedObstacle, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(0, 646) + constructedObstacle->getDimension() * 0.5f);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(74, 28) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(266, 28) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(1060, 28) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(182, 615) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	constructedEnemy = new Board::EnemyPlacement(GameObject::ObjectType::TURRET, sf::Vector2f(GAME_LEFT, GAME_TOP) + sf::Vector2f(928, 615) + sf::Vector2f(Turret::TURRET_WIDTH, Turret::TURRET_HEIGHT) * 0.5f);
	constructedBoard->addEnemy(constructedEnemy);

	listOfBoards.push_back(constructedBoard);
	addObject(constructedBoard);

	return true;
}

/// <summary>
/// Initialise toutes les textures utilisées dans le jeu.
/// </summary>
/// <returns>true si toutes les textures ont été initialisées correctement.</returns>
bool GameScene::init_allTextures()
{
	// Le joueur.
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\player.png", TEXTURE_PLAYER))
	{
		return false;
	}

	// Le bouclier.
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\shield.png", TEXTURE_SHIELD))
	{
		return false;
	}
	// L'option.
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\option.png", TEXTURE_OPTION))
	{
		return false;
	}

	// L'enemi
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\Enemi.png", TEXTURE_ENEMI))
	{
		return false;
	}

	// Les objets du niveau.
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\space_ground.png", TEXTURE_SPACE_GROUND))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\cave_floor_1.png", TEXTURE_CAVE_FLOOR_1))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\cave_floor_2.png", TEXTURE_CAVE_FLOOR_2))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\cave_floor_3.png", TEXTURE_CAVE_FLOOR_3))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\cave_floor_4.png", TEXTURE_CAVE_FLOOR_4))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\cave_floor_5.png", TEXTURE_CAVE_FLOOR_5))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\cave_roof_1.png", TEXTURE_CAVE_ROOF_1))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\cave_roof_2.png", TEXTURE_CAVE_ROOF_2))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\cave_roof_3.png", TEXTURE_CAVE_ROOF_3))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\cave_roof_4.png", TEXTURE_CAVE_ROOF_4))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\cave_roof_5.png", TEXTURE_CAVE_ROOF_5))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\cave_wall_1.png", TEXTURE_CAVE_WALL_1))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\cave_wall_2.png", TEXTURE_CAVE_WALL_2))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\cave_wall_3.png", TEXTURE_CAVE_WALL_3))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\cave_wall_4.png", TEXTURE_CAVE_WALL_4))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\cave_wall_5.png", TEXTURE_CAVE_WALL_5))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\factory_entrance_bottom.png", TEXTURE_FACTORY_ENTRANCE_BOTTOM))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\factory_entrance_top.png", TEXTURE_FACTORY_ENTRANCE_TOP))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\factory_entrance_wall.png", TEXTURE_FACTORY_ENTRANCE_WALL))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\factory_floor.png", TEXTURE_FACTORY_FLOOR))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\factory_obstacle.png", TEXTURE_FACTORY_OBSTACLE))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\factory_roof.png", TEXTURE_FACTORY_ROOF))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\factory_wall.png", TEXTURE_FACTORY_WALL))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\factory_window.png", TEXTURE_FACTORY_WINDOW))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\pipe_big.png", TEXTURE_PIPE_BIG))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\pipe_small.png", TEXTURE_PIPE_SMALL))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\space_hill_1.png", TEXTURE_SPACE_HILL_1))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\space_hill_2.png", TEXTURE_SPACE_HILL_2))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\space_hill_3.png", TEXTURE_SPACE_HILL_3))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\space_hill_4.png", TEXTURE_SPACE_HILL_4))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\space_hill_5.png", TEXTURE_SPACE_HILL_5))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Level\\space_rock.png", TEXTURE_SPACE_ROCK))
	{
		return false;
	}

	// Les images de fond.
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Background\\Layer1.png", TEXTURE_BACKGROUND_LAYER1))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Background\\Layer2.png", TEXTURE_BACKGROUND_LAYER2))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Background\\Layer3.png", TEXTURE_BACKGROUND_LAYER3))
	{
		return false;
	}
	//La turret
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\turret.png", TEXTURE_TURRET))
	{
		return false;
	}
	//projectile de la tourelle
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\fireball.png", TEXTURE_PROJECTILE_TURRET))
	{
		return false;
	}
	//Projectile rouge
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\laserbeam.png", TEXTURE_PROJECTILE_RED))
	{
		return false;
	}
	// Le HUD.
	if (!ressourceManager->addTexture("Ressources\\Sprites\\HUD\\hud.png", TEXTURE_HUD))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\HUD\\hud_multipliers.png", TEXTURE_HUD_MULTIPLIERS))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\HUD\\hud_shield.png", TEXTURE_HUD_SHIELD))
	{
		return false;
	}

	// Les bonus.
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\bonus_shield.png", TEXTURE_BONUS_SHIELD))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\bonus_electro_bomb.png", TEXTURE_BONUS_ELECTRO_BOMB))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\bonus_explosive_bomb.png", TEXTURE_BONUS_EXPLOSIVE_BOMB))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\bonus_option.png", TEXTURE_BONUS_OPTION))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\bonus_points.png", TEXTURE_BONUS_POINTS))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\bonus_weapon.png", TEXTURE_BONUS_WEAPON))
	{
		return false;
	}

	// Les ennemis.
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\stalker.png", TEXTURE_STALKER))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\shadow.png", TEXTURE_SHADOW))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\trooper.png", TEXTURE_TROOPER))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\follower.png", TEXTURE_FOLLOWER))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\crusher.png", TEXTURE_CRUSHER))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\carrier.png", TEXTURE_CARRIER))
	{
		return false;
	}

	// Le cargo.
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\cargo.png", TEXTURE_CARGO))
	{
		return false;
	}

	// Les projectiles.
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\beam.png", TEXTURE_BEAM))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\plasmaBall.png", TEXTURE_PLASMA_BALL))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\twist.png", TEXTURE_TWIST))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\slash.png", TEXTURE_SLASH))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\lazer.png", TEXTURE_LAZER))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Objects\\energyBall.png", TEXTURE_ENERGY_BALL))
	{
		return false;
	}

	return true;
}

/// <summary>
/// Initialise tous les sprites utilisés dans le jeu.
/// </summary>
void GameScene::init_allSprites()
{
	// Le joueur.
	ressourceManager->addSprite(TEXTURE_PLAYER, SPRITE_PLAYER);
	// Le bouclier.
	ressourceManager->addSprite(TEXTURE_SHIELD, SPRITE_SHIELD);
	//L'enemi
	ressourceManager->addSprite(TEXTURE_ENEMI, SPRITE_ENEMI);
	// L'option.
	ressourceManager->addSprite(TEXTURE_OPTION, SPRITE_OPTION);
	// Les objets du niveau.
	ressourceManager->addSprite(TEXTURE_SPACE_GROUND, SPRITE_SPACE_GROUND);
	ressourceManager->addSprite(TEXTURE_CAVE_FLOOR_1, SPRITE_CAVE_FLOOR_1);
	ressourceManager->addSprite(TEXTURE_CAVE_FLOOR_2, SPRITE_CAVE_FLOOR_2);
	ressourceManager->addSprite(TEXTURE_CAVE_FLOOR_3, SPRITE_CAVE_FLOOR_3);
	ressourceManager->addSprite(TEXTURE_CAVE_FLOOR_4, SPRITE_CAVE_FLOOR_4);
	ressourceManager->addSprite(TEXTURE_CAVE_FLOOR_5, SPRITE_CAVE_FLOOR_5);
	ressourceManager->addSprite(TEXTURE_CAVE_ROOF_1, SPRITE_CAVE_ROOF_1);
	ressourceManager->addSprite(TEXTURE_CAVE_ROOF_2, SPRITE_CAVE_ROOF_2);
	ressourceManager->addSprite(TEXTURE_CAVE_ROOF_3, SPRITE_CAVE_ROOF_3);
	ressourceManager->addSprite(TEXTURE_CAVE_ROOF_4, SPRITE_CAVE_ROOF_4);
	ressourceManager->addSprite(TEXTURE_CAVE_ROOF_5, SPRITE_CAVE_ROOF_5);
	ressourceManager->addSprite(TEXTURE_CAVE_WALL_1, SPRITE_CAVE_WALL_1);
	ressourceManager->addSprite(TEXTURE_CAVE_WALL_2, SPRITE_CAVE_WALL_2);
	ressourceManager->addSprite(TEXTURE_CAVE_WALL_3, SPRITE_CAVE_WALL_3);
	ressourceManager->addSprite(TEXTURE_CAVE_WALL_4, SPRITE_CAVE_WALL_4);
	ressourceManager->addSprite(TEXTURE_CAVE_WALL_5, SPRITE_CAVE_WALL_5);
	ressourceManager->addSprite(TEXTURE_FACTORY_ENTRANCE_BOTTOM, SPRITE_FACTORY_ENTRANCE_BOTTOM);
	ressourceManager->addSprite(TEXTURE_FACTORY_ENTRANCE_TOP, SPRITE_FACTORY_ENTRANCE_TOP);
	ressourceManager->addSprite(TEXTURE_FACTORY_ENTRANCE_WALL, SPRITE_FACTORY_ENTRANCE_WALL);
	ressourceManager->addSprite(TEXTURE_FACTORY_FLOOR, SPRITE_FACTORY_FLOOR);
	ressourceManager->addSprite(TEXTURE_FACTORY_OBSTACLE, SPRITE_FACTORY_OBSTACLE);
	ressourceManager->addSprite(TEXTURE_FACTORY_ROOF, SPRITE_FACTORY_ROOF);
	ressourceManager->addSprite(TEXTURE_FACTORY_WALL, SPRITE_FACTORY_WALL);
	ressourceManager->addSprite(TEXTURE_FACTORY_WINDOW, SPRITE_FACTORY_WINDOW);
	ressourceManager->addSprite(TEXTURE_PIPE_BIG, SPRITE_PIPE_BIG);
	ressourceManager->addSprite(TEXTURE_PIPE_SMALL, SPRITE_PIPE_SMALL);
	ressourceManager->addSprite(TEXTURE_SPACE_HILL_1, SPRITE_SPACE_HILL_1);
	ressourceManager->addSprite(TEXTURE_SPACE_HILL_2, SPRITE_SPACE_HILL_2);
	ressourceManager->addSprite(TEXTURE_SPACE_HILL_3, SPRITE_SPACE_HILL_3);
	ressourceManager->addSprite(TEXTURE_SPACE_HILL_4, SPRITE_SPACE_HILL_4);
	ressourceManager->addSprite(TEXTURE_SPACE_HILL_5, SPRITE_SPACE_HILL_5);
	ressourceManager->addSprite(TEXTURE_SPACE_ROCK, SPRITE_SPACE_ROCK);

	// Les images de fond.
	ressourceManager->addSprite(TEXTURE_BACKGROUND_LAYER1, SPRITE_BACKGROUND_LAYER1);
	ressourceManager->addSprite(TEXTURE_BACKGROUND_LAYER2, SPRITE_BACKGROUND_LAYER2);
	ressourceManager->addSprite(TEXTURE_BACKGROUND_LAYER3, SPRITE_BACKGROUND_LAYER3);
	//la tourelle
	ressourceManager->addSprite(TEXTURE_TURRET, SPRITE_TURRET);
	//projectile de la tourelle
	ressourceManager->addSprite(TEXTURE_PROJECTILE_TURRET, SPRITE_PROJECTILE_TURRET);
	//projectile rouge
	ressourceManager->addSprite(TEXTURE_PROJECTILE_RED, SPRITE_PROJECTILE_RED);

	// HUD
	ressourceManager->addSprite(TEXTURE_HUD, SPRITE_HUD);
	ressourceManager->addSprite(TEXTURE_HUD_MULTIPLIERS, SPRITE_HUD_MULTIPLIERS);
	ressourceManager->addSprite(TEXTURE_HUD_SHIELD, SPRITE_HUD_SHIELD);

	// Les bonus.
	ressourceManager->addSprite(TEXTURE_BONUS_SHIELD, SPRITE_BONUS_SHIELD);
	ressourceManager->addSprite(TEXTURE_BONUS_ELECTRO_BOMB, SPRITE_BONUS_ELECTRO_BOMB);
	ressourceManager->addSprite(TEXTURE_BONUS_EXPLOSIVE_BOMB, SPRITE_BONUS_EXPLOSIVE_BOMB);
	ressourceManager->addSprite(TEXTURE_BONUS_OPTION, SPRITE_BONUS_OPTION);
	ressourceManager->addSprite(TEXTURE_BONUS_POINTS, SPRITE_BONUS_POINTS);
	ressourceManager->addSprite(TEXTURE_BONUS_WEAPON, SPRITE_BONUS_WEAPON);


	// Les ennemis.
	ressourceManager->addSprite(TEXTURE_STALKER, SPRITE_STALKER);
	ressourceManager->addSprite(TEXTURE_SHADOW, SPRITE_SHADOW);
	ressourceManager->addSprite(TEXTURE_TROOPER, SPRITE_TROOPER);
	ressourceManager->addSprite(TEXTURE_FOLLOWER, SPRITE_FOLLOWER);
	ressourceManager->addSprite(TEXTURE_CRUSHER, SPRITE_CRUSHER);
	ressourceManager->addSprite(TEXTURE_CARRIER, SPRITE_CARRIER);

	// Le cargo.
	ressourceManager->addSprite(TEXTURE_CARGO, SPRITE_CARGO);

	// Les projectiles.
	ressourceManager->addSprite(TEXTURE_BEAM, SPRITE_BEAM);
	ressourceManager->addSprite(TEXTURE_PLASMA_BALL, SPRITE_PLASMA_BALL);
	ressourceManager->addSprite(TEXTURE_SLASH, SPRITE_SLASH);
	ressourceManager->addSprite(TEXTURE_TWIST, SPRITE_TWIST);
	ressourceManager->addSprite(TEXTURE_LAZER, SPRITE_LAZER);
	ressourceManager->addSprite(TEXTURE_ENERGY_BALL, SPRITE_ENERGY_BALL);
}

/// <summary>
/// Initialise tous les textes utilisés dans le jeu.
/// </summary>
/// <returns>true si tous les textes ont pu s'initialiser correctement; false sinon.</returns>
bool GameScene::init_allTexts()
{
	// La police.
	if (!font.loadFromFile("Ressources\\Fonts\\Inky Thin Pixels.ttf"))
	{
		return false;
	}

	Text* text = nullptr;

	// Le texte pour le score.
	ressourceManager->addText("Score: ", TEXT_SCORE);
	text = ressourceManager->getText(TEXT_SCORE);
	text->setFont(font);
	text->setFillColor(Color::White);
	text->setCharacterSize(SCORE_FONT_SIZE);

	// Le texte pour afficher la vie des boucliers.
	ressourceManager->addText("0", TEXT_SHIELD_LIFE);
	text = ressourceManager->getText(TEXT_SHIELD_LIFE);
	text->setFont(font);
	text->setFillColor(Color::White);
	text->setCharacterSize(SHIELD_LIFE_FONT_SIZE);
	text->setOutlineColor(Color::Black);
	text->setOutlineThickness(1);

	// Le texte pour afficher le nom et les munitions des armes.
	ressourceManager->addText("Name", TEXT_WEAPON_NAME);
	text = ressourceManager->getText(TEXT_WEAPON_NAME);
	text->setFont(font);
	text->setFillColor(Color::White);
	text->setCharacterSize(WEAPON_NAME_FONT_SIZE);

	// Le texte pour afficher la vie restante du joueur.
	ressourceManager->addText("Life", TEXT_LIFE);
	text = ressourceManager->getText(TEXT_LIFE);
	text->setFont(font);
	text->setFillColor(Color::White);
	text->setCharacterSize(LIFE_FONT_SIZE);

}

/// <summary>
/// Gère les abonnements de tous les objets.
/// </summary>
void GameScene::init_allSubscriptions()
{
	for (unsigned int i = 0; i < NBR_OF_GAMEOBJECTS; ++i)
	{
		if (allGameObjects[i] != nullptr)
		{
			GameObject::ObjectType objectType = allGameObjects[i]->getType();

			// Les abonnements aux bonus -------------------------------------------------------------------
			if (Bonus* bonus = dynamic_cast<Bonus*>(allGameObjects[i]))
			{

				// Abonnements au ShieldAdder ------------------------------------
				if (objectType == GameObject::ObjectType::SHIELD_ADDER)
				{
					// Le HUD, le joueur et la scène de jeu.
					bonus->ajouterObservateur(hud);
					bonus->ajouterObservateur(player);
					bonus->ajouterObservateur(this);
				}
				// Abonnements à l'ElectroBomb -----------------------------------
				else if (objectType == GameObject::ObjectType::ELECTRO_BOMB)
				{
					// Tous les ennemis et le joueur.
					for (unsigned int j = 0; j < NBR_OF_GAMEOBJECTS; ++j)
					{
						if (allGameObjects[j] != nullptr)
						{
							if (Enemy* enemy = dynamic_cast<Enemy*>(allGameObjects[j]))
							{
								bonus->ajouterObservateur(enemy);
							}
						}
					}
					bonus->ajouterObservateur(player);
				}
				// Abonnements à l'ExplosiveBomb ---------------------------------
				else if (objectType == GameObject::ObjectType::EXPLOSIVE_BOMB)
				{
					// Tous les ennemis, le joueur et la scène.
					for (unsigned int j = 0; j < NBR_OF_GAMEOBJECTS; ++j)
					{
						if (allGameObjects[j] != nullptr)
						{
							if (Enemy* enemy = dynamic_cast<Enemy*>(allGameObjects[j]))
							{
								bonus->ajouterObservateur(enemy);
							}
						}
					}
					bonus->ajouterObservateur(player);
					bonus->ajouterObservateur(this);
				}
				// Abonnements à l'OptionAdder -----------------------------------
				else if (objectType == GameObject::ObjectType::OPTION_ADDER)
				{
					// Le joueur.
					bonus->ajouterObservateur(player);
				}
				// Abonnements au PointsMultiplicator ----------------------------
				else if (objectType == GameObject::ObjectType::POINTS_MULTIPLICATOR)
				{
					// Le HUD.
					bonus->ajouterObservateur(hud);
				}
				// Abonnements aux WeaponAdders ----------------------------------
				else if (GameObject::isWeaponAdder(objectType))
				{
					// Le HUD.
					bonus->ajouterObservateur(hud);
				}
			}
			// Les abonnements aux ennemis --------------------------------------------------------------
			if (Enemy* enemy = dynamic_cast<Enemy*>(allGameObjects[i]))
			{
				// Le HUD et la scène.
				enemy->ajouterObservateur(hud);
				enemy->ajouterObservateur(this);
			}
		}
	}

	// Les abonnements au joueur --------------------------------------------------------------------
	// Le HUD.
	player->ajouterObservateur(hud);
}

/// <summary>
/// Gère toutes les commandes entrées dans la scène de jeu.
/// </summary>
void GameScene::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		// Si le joueur ferme la fenêtre...
		if (event.type == Event::Closed)
		{
			// On fait une transition vers la scène de sortie.
			isRunning = false;
			transitionVersScene = Scene::scenes::EXIT;
		}
		//si le joueur joue avec une manette
		if (sf::Joystick::isConnected(0))
		{
			//LB
			if (sf::Joystick::isButtonPressed(0, 4))
			{
				hud->selectLeftWeapon();
			}
			//RB
			else if (sf::Joystick::isButtonPressed(0, 5))
			{
				hud->selectRightWeapon();
			}
		}

		if (event.type == Event::KeyPressed)
		{
			// Q = changer pour l'arme à gauche.
			if (event.key.code == Keyboard::Q)
			{
				hud->selectLeftWeapon();
			}
			// E = changer pour l'arme à droite.
			else if (event.key.code == Keyboard::E)
			{
				hud->selectRightWeapon();
			}
			// Escape = retour au menu principal.
			else if (event.key.code == Keyboard::Escape)
			{
				isRunning = false;
				transitionVersScene = scenes::TITLE;
			}
		}
	}

	player->getInputs();
}

/// <summary>
/// Met à jour la scène de jeu.
/// </summary>
void GameScene::update()
{
	float deltaT = timer.getElapsedTime().asSeconds() - tempsDernierUpdate.asSeconds();
	tempsDernierUpdate = timer.getElapsedTime();
	//float deltaT = 1.0f / 60.0f;

	// Met à jour le visuel de l'explosion.
	if (isExploding)
	{
		timerExplosion -= sf::seconds(deltaT);

		if (timerExplosion.asMilliseconds() <= 0)
		{
			isExploding = false;
		}
	}

	// Met à jour tous les objets.
	for (IUpdatable* updatable : allUpdatable)
	{
		updatable->update(deltaT);
	}
	
	// Met à jour le HUD et l'arme en cours.
	hud->setLife(player->getLife());
	hud->setLastShieldLife(player->getLastShieldLife());
	player->changeWeapon(hud->getCurrentWeapon());
	
	update_manageCollisions();

	update_level();

	for (IUpdatable* updatable : updatablesToRemove)
	{
		allUpdatable.remove(updatable);
	}
	updatablesToRemove.clear();

	hud->deleteUnusedWeapons();

	// Conditions pour que la partie soit terminée:

	//Si le joueur est détruit (le joueur a donc perdu).
	if (player->isDestroyed())
	{
		gameCompleted = false;
		isRunning = false;
		transitionVersScene = scenes::END;
	}

	// Si le joueur a tué le stalker de mi-niveau et celui de fin de niveau (le joueur a donc gagné).
	if (nbrOfStalkerKilled >= 2)
	{
		gameCompleted = true;
		isRunning = false;
		transitionVersScene = scenes::END;
	}
	/*if (player->getPlayerInputs().getCommands()== PlayerCommand_Fire)
	{

	}*/
}

/// <summary>
/// Met à jour le niveau.
/// </summary>
void GameScene::update_level()
{
	// Si la première board a dépassé la vue par la gauche.
	if (listOfBoards[currentBoard]->getPosition().x <= -listOfBoards[currentBoard]->getDimension().x * 0.5f + GameScene::GAME_LEFT)
	{
		// On la désactive.
		listOfBoards[currentBoard]->deactivate();

		// On choisi la nouvelle board.
		currentBoard = nextBoard;
		nextBoard = nextBoard + 1 >= listOfBoards.size() ? nextBoard - 1 : nextBoard + 1;

		// Et on la place derrière l'autre board.
		listOfBoards[nextBoard]->activate(listOfBoards[currentBoard]->getPosition() + sf::Vector2f(listOfBoards[currentBoard]->getDimension().x, 0));
	}
}

/// <summary>
/// Gère les collisions.
/// </summary>
void GameScene::update_manageCollisions()
{
	// Pour tous les objets du jeu...
	for (unsigned int i = 0; i < NBR_OF_GAMEOBJECTS; i++)
	{
		// S'il n'est pas nul...
		if (allGameObjects[i] != nullptr)
		{
			// Collision des ennemis --------------------------------------------------------------------
			if (Enemy* enemy = dynamic_cast<Enemy*>(allGameObjects[i]))
			{
				// S'il est activé.
				if (enemy->isActivated())
				{
					// On regarde la collision avec les autres objets activables.
					for (Activatable* activatable : allActivatable)
					{
						// Si l'objet est activé.
						if (activatable->isActivated())
						{
							// Collision entre ennemi et projectile --------------------
							if (Projectile* projectile = dynamic_cast<Projectile*>(activatable))
							{
								if (GameObject::isProjectile(projectile->getType()) && !GameObject::isEnemyProjectile(projectile->getType()))
								{
									if (enemy->collidesWith(*projectile))
									{
										// L'enemi perd de la vie et le projectile se désactive.
										enemy->damage(projectile->getPower());
										projectile->deactivate();
									}
								}
							}
							// Collision entre ennemi et bombes ------------------------
							else if (Bonus* bonus = dynamic_cast<Bonus*>(activatable))
							{
								if (bonus->getType() == GameObject::ObjectType::ELECTRO_BOMB
									|| bonus->getType() == GameObject::ObjectType::EXPLOSIVE_BOMB)
								{
									if (enemy->collidesWith(*bonus))
									{
										// L'ennemi ramasse le bonus.
										bonus->pick(enemy);
									}
								}
							}
						}
					}

					// Collision entre ennemi et joueur ----------------------------
					if (enemy->collidesWith(*player))
					{
						// On endommage le joueur, on détruit l'ennemi et on donne une certaine période d'invincibilité au joueur.
						player->damage(enemy->getCollisionDamage());
						enemy->damage(9999);
						player->setInvincivility(1000);
					}
				}
			}
			// Collision des projectiles -------------------------------------------------------------------
			else if (Projectile* projectile = dynamic_cast<Projectile*>(allGameObjects[i]))
			{
				if (projectile->isActivated())
				{
					// On regarde la collision avec les autres objets activables.
					for (Activatable* activatable : allActivatable)
					{
						// Si l'autre objet est activé...
						if (activatable->isActivated())
						{
							// Collision entre projectile et bombe explosive -----------
							if (Bonus* bonus = dynamic_cast<Bonus*>(activatable))
							{
								if (bonus->getType() == GameObject::ObjectType::EXPLOSIVE_BOMB)
								{
									if (projectile->collidesWith(*bonus))
									{
										// L'ennemi ramasse le bonus.
										bonus->pick(projectile);
									}
								}
							}
							// Collision entre projectile allié et projectile ennmi ----
							else if (EnemyProjectile* enemyProjectile = dynamic_cast<EnemyProjectile*>(activatable))
							{
								if (!GameObject::isEnemyProjectile(projectile->getType()))
								{
									if (projectile->collidesWith(*enemyProjectile))
									{
										// Le projectile ennemi subit des dégâts et le projectile allié se désactive.
										enemyProjectile->damage(projectile->getPower());
										projectile->deactivate();
									}
								}
							}
							// Collision entre projectile allié et cargo ---------------
							else if (Cargo* cargo = dynamic_cast<Cargo*>(activatable))
							{
								if (!cargo->isDestroyed())
								{
									if (!GameObject::isEnemyProjectile(projectile->getType()))
									{
										if (projectile->collidesWith(*cargo))
										{
											// Le cargo perd de la vie et le projectile se désactive.
											cargo->damage(projectile->getPower());
											projectile->deactivate();
										}
									}
								}
							}
						}
					}
					// Collision entre projectile ennemi et joueur -----------------
					if (GameObject::isEnemyProjectile(projectile->getType()))
					{
						if (projectile->collidesWith(*player))
						{
							// On fait subir des dégâts au joueur et on désactive le projetile ennemi.
							EnemyProjectile* enemyProjectile = (EnemyProjectile*)projectile;
							player->damage(enemyProjectile->getPower(), enemyProjectile->getColor());
							enemyProjectile->deactivate();
						}
					}
				}
			}
			// Collision des bonus ----------------------------------------------------------------------
			else if (Bonus* bonus = dynamic_cast<Bonus*>(allGameObjects[i]))
			{
				// S'il est activé...
				if (bonus->isActivated())
				{
					// Collision entre bonus et joueur -----------------------------
					if (bonus->collidesWith(*player))
					{
						// Le joueur rammasse le bonus.
						bonus->pick(player);
					}
				}
			}
		}
	}

	// Collision du joueur --------------------------------------------------------------------------
	// Collision entre joueur et obstacles ---------------------------------
	if (listOfBoards[currentBoard]->collidesWith(*player) || listOfBoards[nextBoard]->collidesWith(*player))
	{
		// Le joueur perd de la vie est devient invincible pendant une certaine période.
		player->damage(BoardObstacle::OBSTACLE_DAMMAGE);
		player->setInvincivility(2500);
	}
}

/// <summary>
/// Affiche la scène de jeu.
/// </summary>
void GameScene::draw()
{
	mainWin->clear();

	// On affiche tous les objets de jeu qui existent.
	for (unsigned int i = 0; i < NBR_OF_GAMEOBJECTS; i++)
	{
		if (allGameObjects[i] != nullptr)
		{
			allGameObjects[i]->draw(*mainWin);
		}
	}

	if (isExploding)
	{
		mainWin->draw(explosion);
	}

	mainWin->display();
}

/// <summary>
/// Ajoute un objet à la scène.
/// </summary>
/// <param name="object">L'objet à ajouter.</param>
/// <returns>true si l'objet a pu être ajouté; false sinon.</returns>
bool GameScene::addObject(GameObject* object)
{
	// On l'ajoute à la liste des objets.
	bool placeFoundForObject = false;
	unsigned int place = 0;
	while (place < NBR_OF_GAMEOBJECTS && !placeFoundForObject)
	{
		if (allGameObjects[place] == nullptr)
		{
			allGameObjects[place] = object;
			placeFoundForObject = true;
		}

		place++;
	}

	// Condition d'échec: il ne reste plus de place pour ajouter l'objet.
	if (!placeFoundForObject)
	{
		delete object;
		return false;
	}

	// Si c'est un Updatable...
	if (IUpdatable* updatable = dynamic_cast<IUpdatable*>(object))
	{
		allUpdatable.push_back(updatable);
	}

	// Si c'est une Activatable...
	if (Activatable* activatable = dynamic_cast<Activatable*>(object))
	{
		allActivatable.push_back(activatable);
	}

	// Si c'est un Destroyable...
	if (Destroyable* destroyable = dynamic_cast<Destroyable*>(object))
	{
		allDestroyable.push_back(destroyable);
	}

	return true;
}

/// <summary>
/// Ajoute un objet qui peut se mettre à jour.
/// </summary>
/// <param name="updatable">L'objet à ajouter.</param>
void GameScene::addUpdatable(IUpdatable* updatable)
{
	allUpdatable.push_back(updatable);
}

/// <summary>
/// Retire un objet qui peut se mettre à jour de la liste.
/// </summary>
/// <param name="updatable">L'objet à retirer.</param>
void GameScene::removeUpdatable(IUpdatable* updatable)
{
	updatablesToRemove.push_back(updatable);
}

/// <summary>
/// Active un objet activable dans le jeu.
/// </summary>
/// <param name="type">Le type de l'objet à activer.</param>
/// <param name="position">La position de l'objet une fois activé.</param>
/// <returns>true si l'objet a pu être activé; false sinon.</returns>
bool GameScene::activateObject(const GameObject::ObjectType type, const sf::Vector2f& position)
{
	bool objectActivated = false;

	// Pour tous les objets activables...
	for (Activatable* activatable : allActivatable)
	{
		// Si l'objet n'est pas déjà actif.
		if (!activatable->isActivated())
		{
			// On doit le caster en GameObject pour vérifier son type :'(
			if (GameObject* object = dynamic_cast<GameObject*>(activatable))
			{
				// Si le type est le bon...
				if (object->getType() == type)
				{
					// On l'active à la position voulue.
					activatable->activate(position);
					objectActivated = true;
					break;
				}
			}
		}
	}

	return objectActivated;
}

/// <summary>
/// Active un objet activable dans le jeu.
/// </summary>
/// <param name="type">Le type de l'objet à activer.</param>
/// <param name="posX">La position de l'objet en X une fois activé.</param>
/// <param name="posY">La position de l'objet en Y une fois activé.</param>
/// <returns>true si l'objet a pu être activé; false sinon.</returns>
bool GameScene::activateObject(const GameObject::ObjectType type, const float posX, const float posY)
{
	sf::Vector2f pos(posX, posY);
	return activateObject(type, pos);
}

/// <summary>
/// Active un objet qui peut bouger.
/// </summary>
/// <param name="type">Le type de l'objet à activer.</param>
/// <param name="position">La position de l'objet une fois activé.</param>
/// <param name="direction">La direction avec laquelle activer l'objet.</param>
/// <returns>true si l'objet a pu être activé; false sinon.</returns>
bool GameScene::activateMovable(const GameObject::ObjectType type, const sf::Vector2f& position, const sf::Vector2f& direction)
{
	bool objectActivated = false;

	// Pour tous les objets activables...
	for (Activatable* activatable : allActivatable)
	{
		// Si l'objet n'est pas déjà actif.
		if (!activatable->isActivated())
		{
			// On doit le caster en Movable
			if (Movable* object = dynamic_cast<Movable*>(activatable))
			{
				// Si le type est le bon...
				if (object->getType() == type)
				{
					// On l'active à la position voulue.
					activatable->activate(position);
					object->setDirection(direction);
					objectActivated = true;
					break;
				}
			}
			else
			{
				assert(false && "L'objet activé à l'aide de activateMovable doit être un Movable.");
			}
		}
	}

	return objectActivated;
}

/// <summary>
/// Active un objet qui peut bouger.
/// </summary>
/// <param name="type">Le type de l'objet à activer.</param>
/// <param name="posX">La position de l'objet en X une fois activé.</param>
/// <param name="posY">La position de l'objet en Y une fois activé.</param>
/// <param name="direction">La direction avec laquelle activer l'objet.</param>
/// <returns>true si l'objet a pu être activé; false sinon.</returns>
bool GameScene::activateMovable(const GameObject::ObjectType type, const float posX, const float posY, const sf::Vector2f& direction)
{
	sf::Vector2f pos(posX, posY);
	return activateMovable(type, pos, direction);
}

/// <summary>
/// Active un objet qui peut bouger.
/// </summary>
/// <param name="type">Le type de l'objet à activer.</param>
/// <param name="position">La position de l'objet une fois activé.</param>
/// <param name="direction">La direction avec laquelle activer l'objet.</param>
/// <returns>true si l'objet a pu être activé; false sinon.</returns>
bool GameScene::activateMovable(const GameObject::ObjectType type, const sf::Vector2f& position, const	Movable::Direction direction)
{
	sf::Vector2f dir = Movable::convertDirection(direction);
	return activateMovable(type, position, dir);
}

/// <summary>
/// Active un objet qui peut bouger.
/// </summary>
/// <param name="type">Le type de l'objet à activer.</param>
/// <param name="posX">La position de l'objet en X une fois activé.</param>
/// <param name="posY">La position de l'objet en Y une fois activé.</param>
/// <param name="direction">La direction avec laquelle activer l'objet.</param>
/// <returns>true si l'objet a pu être activé; false sinon.</returns>
bool GameScene::activateMovable(const GameObject::ObjectType type, const float posX, const float posY, const Movable::Direction direction)
{
	sf::Vector2f dir = Movable::convertDirection(direction);
	sf::Vector2f pos(posX, posY);
	return activateMovable(type, pos, dir);
}

/// <summary>
/// Active un objet qui peut bouger.
/// </summary>
/// <param name="type">Le type de l'objet à activer.</param>
/// <param name="position">La position de l'objet une fois activé.</param>
/// <param name="angle">L'angle avec lequel ativer l'objet.</param>
/// <returns>true si l'objet a pu être activé; false sinon.</returns>
bool GameScene::activateMovable(const GameObject::ObjectType type, const sf::Vector2f& position, const	float angle)
{
	sf::Vector2f dir = Movable::convertDirection(angle);
	return activateMovable(type, position, dir);
}

/// <summary>
/// Active un objet qui peut bouger.
/// </summary>
/// <param name="type">Le type de l'objet à activer.</param>
/// <param name="posX">La position de l'objet en X une fois activé.</param>
/// <param name="posY">La position de l'objet en Y une fois activé.</param>
/// <param name="angle">L'angle avec lequel ativer l'objet.</param>
/// <returns>true si l'objet a pu être activé; false sinon.</returns>
bool GameScene::activateMovable(const GameObject::ObjectType type, const float posX, const float posY, const float angle)
{
	sf::Vector2f dir = Movable::convertDirection(angle);
	sf::Vector2f pos(posX, posY);
	return activateMovable(type, pos, dir);
}

/// <summary>
/// Active un objet de type EnemyProjectile.
/// </summary>
/// <param name="type">Le type de l'objet à activer.</param>
/// <param name="enemy">L'ennemi qui active le projectile.</param>
/// <param name="direction">La direction avec laquelle activer l'objet.</param>
/// <param name="position">La position de l'objet une fois activé.</param>
/// <returns>true si l'objet a pu être activé; false sinon.</returns>
bool GameScene::activateEnemyProjectile(const GameObject::ObjectType type, const Enemy* enemy, const sf::Vector2f& direction, const sf::Vector2f position)
{
	bool objectActivated = false;

	// Pour tous les objets activables...
	for (Activatable* activatable : allActivatable)
	{
		// Si l'objet n'est pas déjà actif.
		if (!activatable->isActivated())
		{
			// On doit le caster en Objet
			if (GameObject* object = dynamic_cast<GameObject*>(activatable))
			{
				// Si le type est le bon...
				if (object->getType() == type)
				{
					if (EnemyProjectile* enemyProjectile = dynamic_cast<EnemyProjectile*>(object))
					{
						// On l'active à la position voulue.
						sf::Vector2f newPosition;
						if (position == sf::Vector2f(0, 0))
						{
							newPosition = enemy->getPosition() - sf::Vector2f(enemy->getDimension().x * 0.5f, 0) - sf::Vector2f(object->getDimension().x * 0.5f, 0);
						}
						else
						{
							newPosition = position;
						}
						enemyProjectile->activate(newPosition, enemy->getColor());
						enemyProjectile->setDirection(direction);
						objectActivated = true;
						break;
					}
					else
					{
						assert(false && "L'objet activé à l'aide de activateEnemyProjectile doit être un EnemyProjectile.");
					}
				}
			}

		}
	}

	return objectActivated;
}

/// <summary>
/// Active un objet de type EnemyProjectile.
/// </summary>
/// <param name="type">Le type de l'objet à activer.</param>
/// <param name="enemy">L'ennemi qui active le projectile.</param>
/// <param name="direction">La direction avec laquelle activer l'objet.</param>
/// <param name="position">La position de l'objet une fois activé.</param>
/// <returns>true si l'objet a pu être activé; false sinon.</returns>
bool GameScene::activateEnemyProjectile(const GameObject::ObjectType type, const Enemy* enemy, const	Movable::Direction direction, const sf::Vector2f position)
{
	sf::Vector2f dir = Movable::convertDirection(direction);
	return activateEnemyProjectile(type, enemy, dir, position);
}

/// <summary>
/// Active un objet de type EnemyProjectile.
/// </summary>
/// <param name="type">Le type de l'objet à activer.</param>
/// <param name="enemy">L'ennemi qui active le projectile.</param>
/// <param name="angle">L'angle avec lequel ativer l'objet.</param>
/// <param name="position">La position de l'objet une fois activé.</param>
/// <returns>true si l'objet a pu être activé; false sinon.</returns>
bool GameScene::activateEnemyProjectile(const GameObject::ObjectType type, const Enemy* enemy, const	float angle, const sf::Vector2f position)
{
	sf::Vector2f dir = Movable::convertDirection(angle);
	return activateEnemyProjectile(type, enemy, dir, position);
}

/// <summary>
/// Notifie le jeu qu'un événement s'est produit.
/// </summary>
/// <param name="sujet">Le sujet qui a appelé l'événement.</param>
void GameScene::notifier(Sujet* sujet)
{
	if (GameObject* object = dynamic_cast<GameObject*>(sujet))
	{
		if (GameObject::ObjectType::SHIELD_ADDER == object->getType())
		{
			hud->setLastShieldLife(player->getLastShieldLife());
		}
		else if (GameObject::isEnemy(object->getType()))
		{
			if (GameObject::ObjectType::CARRIER == object->getType())
			{
				// La destruction d'un Carrier active toujours un bonus.
				activateBonus(object->getPosition());
			}
			else
			{
				// On note le nombre de Stalker morts, car c'est ça qui va indiquer la fin du niveau.
				if (GameObject::ObjectType::STALKER == object->getType())
				{
   					++nbrOfStalkerKilled;
				}
				
				int probability = rand() % 100;
				if (probability <= POURCENTAGE_BONUS_SPAWN)
				{
					activateBonus(object->getPosition());
				}
			}
		}
		else if (GameObject::ObjectType::EXPLOSIVE_BOMB == object->getType())
		{
			ExplosiveBomb* explosiveBomb = dynamic_cast<ExplosiveBomb*>(object);

			isExploding = true;
			timerExplosion = sf::milliseconds(MS_OF_EXPLOSION);
			explosion.setFillColor(explosiveBomb->getColor());
		}
	}
}

/// <summary>
/// Active un ennemi de type Follower.
/// </summary>
/// <param name="followed">L'ennemi de type Followed qui a activé le Follower.</param>
/// <returns>true si l'objet a pu être activé; false sinon.</returns>
bool GameScene::activateFollower(Followed* followed)
{
	bool objectActivated = false;

	// Pour tous les objets activables...
	for (Activatable* activatable : allActivatable)
	{
		// Si l'objet n'est pas déjà actif.
		if (!activatable->isActivated())
		{
			if (Follower* follower = dynamic_cast<Follower*>(activatable))
			{
				objectActivated = true;
				follower->activate(followed);
				break;
			}
		}
	}

	return objectActivated;
}

/// <summary>
/// Retourne le score du joueur.
/// </summary>
/// <returns>Le score du joueur.</returns>
unsigned int GameScene::getScore()
{
	if (isRunning)
	{
		return hud->getScore();
	}
	else
	{
		return scoreFinal;
	}
}

/// <summary>
/// Détermine si le joueur a gagnée la partie.
/// </summary>
/// <returns>true si le joeur a gagné la partie; false sinon.</returns>
bool GameScene::isCompleted()
{
	return gameCompleted;
}

/// <summary>
/// Active un bonus aléatoire.
/// </summary>
/// <param name="position">La position à laquelle activer le bonus..</param>
/// <returns>true si l'objet a pu être activé; false sinon.</returns> 
bool GameScene::activateBonus(const sf::Vector2f& position)
{
	int pourcentage = rand() % 100;

	GameObject::ObjectType bonusType;
	if (pourcentage < THRESHOLD_DOUBLE_BLASTER_ADDER)
	{
		bonusType = GameObject::ObjectType::DOUBLE_BLASTER_ADDER;
	}
	else if (pourcentage < THRESHOLD_SIDE_BLASTER_ADDER)
	{
		bonusType = GameObject::ObjectType::SIDE_BLASTER_ADDER;
	}
	else if (pourcentage < THRESHOLD_SLASHER_ADDER)
	{
		bonusType = GameObject::ObjectType::SLASHER_ADDER;
	}
	else if (pourcentage < THRESHOLD_TRI_SHOOTER_ADDER)
	{
		bonusType = GameObject::ObjectType::TRI_SHOOTER_ADDER;
	}
	else if (pourcentage < THRESHOLD_TWISTED_SHOOTER_ADDER)
	{
		bonusType = GameObject::ObjectType::TWISTED_SHOOTER_ADDER;
	}
	else if (pourcentage < THRESHOLD_ELECTRO_BOMB)
	{
		bonusType = GameObject::ObjectType::ELECTRO_BOMB;
	}
	else if (pourcentage < THRESHOLD_EXPLOSIVE_BOMB)
	{
		bonusType = GameObject::ObjectType::EXPLOSIVE_BOMB;
	}
	else if (pourcentage < THRESHOLD_OPTION_ADDER)
	{
		bonusType = GameObject::ObjectType::OPTION_ADDER;
	}
	else if (pourcentage < THRESHOLD_POINTS_MULTIPLICATOR)
	{
		bonusType = GameObject::ObjectType::POINTS_MULTIPLICATOR;
	}
	else if (pourcentage < THRESHOLD_SHIELD_ADDER)
	{
		bonusType = GameObject::ObjectType::SHIELD_ADDER;
	}
		 
	activateObject(bonusType, position);

	return true;
}