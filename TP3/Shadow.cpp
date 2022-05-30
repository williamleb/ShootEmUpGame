#include "Shadow.h"
#include "GameScene.h"

using namespace TP3;

const float Shadow::IDLE_THRESHOLD = 10.0f;

const float Shadow::ACCURACY = M_PI_4;

/// <summary>
/// Crée un nouveau <see cref="Shadow"/>.
/// </summary>
Shadow::Shadow()
	: Enemy(ObjectType::SHADOW, SHADOW_FIRERATE, SHADOW_DEFAULT_LIFE, SHADOW_MAX_SPEED, SHADOW_POINTS, SHADOW_COLLISION_DAMAGE),
	isFiring(false), nbrOfFire(0), hasFired(false)
{
}

/// <summary>
/// Update l'ennemi selon le temps écoulé.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la méthode.</param>
void Shadow::update(const float deltaT)
{
	Enemy::update(deltaT);
	if (getState() == Moving && !isFiring)
	{
		setSpeed(getSpeed() - (DECELERATION_VALUE * deltaT));

		if (!hasFired && abs(getSpeed()) <= IDLE_THRESHOLD)
		{
			isFiring = true;
			setSpeed(0);
		}
	}
}

/// <summary>
/// Initialise le Shadow.
/// Doit être appelé une fois avant d'utiliser l'ennemi.
/// </summary>
/// <param name="spriteKey">Le sprite du Follower.</param>
/// <returns>true si l'initialisation s'est bien passée; false sinon.</returns>
bool Shadow::init(const RessourceManager::key spriteKey)
{
	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(SHADOW_WIDTH / 2, SHADOW_HEIGHT / 2);
	setDimension(SHADOW_WIDTH, SHADOW_HEIGHT);

	return true;
}

/// <summary>
/// Fait tirer l'ennemi.
/// </summary>
void Shadow::fire()
{
	if (isFiring)
	{
		float angleDeviation = -ACCURACY + (float)(rand()) / ((float)(RAND_MAX / (ACCURACY + ACCURACY)));

		GameScene* gameScene = getGameScene();
		gameScene->activateEnemyProjectile(ObjectType::ENERGY_BALL, this, getAngleWith(*getPlayer()) + angleDeviation);

		++nbrOfFire;

		if (nbrOfFire >= NBR_OF_FIRE_BEFORE_BACKING)
		{
			isFiring = false;
			hasFired = true;
		}
	}
}

/// <summary>
/// Réinitialise l'ennemi à un état de départ.
/// </summary>
void Shadow::reset()
{
	isFiring = false;
	hasFired = false;
	nbrOfFire = 0;
	Enemy::reset();
}