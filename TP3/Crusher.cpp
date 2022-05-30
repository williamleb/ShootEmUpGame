#include "Crusher.h"
#include "GameScene.h"

using namespace TP3;

const float Crusher::ROTATION_SPEED = 1.5f;

const float Crusher::MAX_ANGLE = M_PI_2;
const float Crusher::MIN_ANGLE = 0;

const float Crusher::ACCURACY = M_PI / 6;

/// <summary>
/// Crée un nouveau <see cref="Crusher"/>.
/// </summary>
Crusher::Crusher()
	: Enemy(ObjectType::CRUSHER, CRUSHER_FIRERATE, CRUSHER_DEFAULT_LIFE, CRUSHER_DEFAULT_SPEED, CRUSHER_POINTS, CRUSHER_COLLISION_DAMAGE),
	angle(M_PI_4), balance(1)
{
}

/// <summary>
/// Update l'ennemi selon le temps écoulé.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la méthode.</param>
void Crusher::update(const float deltaT)
{
	Enemy::update(deltaT);
	if (getState() == Moving)
	{
		// On fait balancer l'ennemi.
		angle += balance * ROTATION_SPEED * deltaT;

		if (angle > MAX_ANGLE)
		{
			angle = MAX_ANGLE;
			balance = -1;
		}
		else if (angle < MIN_ANGLE)
		{
			angle = MIN_ANGLE;
			balance = 1;
		}

		setDirection(angle);

		Enemy::scroll(deltaT);
	}

	// Si l'ennemi se retrouve en bas complètement, il est désactivé.
	else if (getPosition().y - getDimension().y * 0.5f >= GameScene::GAME_TOP + GameScene::GAME_HEIGHT)
	{
		deactivate();
	}
}

/// <summary>
/// Initialise le Crusher.
/// Doit être appelé une fois avant d'utiliser l'ennemi.
/// </summary>
/// <param name="spriteKey">Le sprite du Follower.</param>
/// <returns>true si l'initialisation s'est bien passée; false sinon.</returns>
bool Crusher::init(const RessourceManager::key spriteKey)
{
	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(CRUSHER_WIDTH / 2, CRUSHER_HEIGHT / 2);
	setDimension(CRUSHER_WIDTH, CRUSHER_HEIGHT);

	return true;
}

/// <summary>
/// Fait tirer l'ennemi.
/// </summary>
void Crusher::fire()
{
	float angleDeviation = -ACCURACY + (float)(rand()) / ((float)(RAND_MAX / (ACCURACY + ACCURACY)));

	GameScene* gameScene = getGameScene();
	gameScene->activateEnemyProjectile(ObjectType::ENERGY_BALL, this, getAngleWith(*getPlayer()) + angleDeviation);
}

/// <summary>
/// Réinitialise l'ennemi à un état de départ.
/// </summary>
void Crusher::reset()
{
	angle = M_PI_4;
	balance = 1;
	Enemy::reset();
}