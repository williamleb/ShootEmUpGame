#include "Trooper.h"
#include "GameScene.h"
#include "Player.h"

using namespace TP3;

const float Trooper::ROTATION_SPEED = 1.5f;

const float Trooper::MAX_ANGLE = 5 * M_PI_4;
const float Trooper::MIN_ANGLE = 3 * M_PI_4;

/// <summary>
/// Crée un nouveau <see cref="Trooper"/>.
/// </summary>
/// <param name="type">Le type d'ennemi créé.</param>
Trooper::Trooper(const GameObject::ObjectType type)
	: Enemy(type, TROOPER_FIRERATE, TROOPER_DEFAULT_LIFE, TROOPER_DEFAULT_SPEED, TROOPER_POINTS, TROOPER_COLLISION_DAMAGE),
	angle(M_PI)
{
}

/// <summary>
/// Crée un nouveau <see cref="Trooper"/>.
/// </summary>
Trooper::Trooper()
	: Trooper(ObjectType::TROOPER)
{
}

/// <summary>
/// Détruit un <see cref="Trooper"/>.
/// </summary>
Trooper::~Trooper()
{
}

/// <summary>
/// Update l'ennemi selon le temps écoulé.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la méthode.</param>
void Trooper::update(const float deltaT)
{
	Enemy::update(deltaT);

	// Le Trooper ne peut pas sortir par le haut ou le bas de l'écran.
	if (getPosition().y - getDimension().y * 0.5f < GameScene::GAME_TOP)
	{
		setPosition(getPosition().x, GameScene::GAME_TOP + getDimension().y * 0.5f);
	}
	else if (getPosition().y + getDimension().y * 0.5f >= GameScene::GAME_TOP + GameScene::GAME_HEIGHT)
	{
		setPosition(getPosition().x, GameScene::GAME_TOP + GameScene::GAME_HEIGHT - 1 - getDimension().y * 0.5f);
	}

	sf::Vector2f pos = getPosition();

	if (getState() == Moving)
	{
		// Le Trooper essait vagement de se rapprocher de l'ennemi.
		// Il zigzague.
		Player* player = getPlayer();
		if (player->getPosition().y <= getPosition().y)
		{
			angle += ROTATION_SPEED * deltaT;
		}
		else
		{
			angle -= ROTATION_SPEED * deltaT;
		}

		if (angle > MAX_ANGLE)
		{
			angle = MAX_ANGLE;
		}
		else if (angle < MIN_ANGLE)
		{
			angle = MIN_ANGLE;
		}

		setDirection(angle);
	}
}

/// <summary>
/// Initialise le Trooper.
/// Doit être appelé une fois avant d'utiliser l'ennemi.
/// </summary>
/// <param name="spriteKey">Le sprite du Follower.</param>
/// <returns>true si l'initialisation s'est bien passée; false sinon.</returns>
bool Trooper::init(const RessourceManager::key spriteKey)
{
	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(TROOPER_WIDTH / 2, TROOPER_HEIGHT / 2);
	setDimension(TROOPER_WIDTH, TROOPER_HEIGHT);

	return true;
}

/// <summary>
/// Fait tirer l'ennemi.
/// </summary>
void Trooper::fire()
{
	GameScene* gameScene = getGameScene();
	gameScene->activateEnemyProjectile(ObjectType::LAZER, this, Direction::LEFT);
}

/// <summary>
/// Réinitialise l'ennemi à un état de départ.
/// </summary>
void Trooper::reset()
{
	angle = M_PI;
	Enemy::reset();
}