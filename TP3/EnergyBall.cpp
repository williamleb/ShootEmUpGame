#include "EnergyBall.h"
#include "GameScene.h"
using namespace TP3;


/// <summary>
/// Crée un nouveau <see cref="Projectile"/>.
/// </summary>
EnergyBall::EnergyBall()
	:EnemyProjectile(GameObject::ENERGY_BALL, ENERGY_BALL_SPEED, ENERGY_BALL_POWER, ENERGY_BALL_HEALTH),
	moveTimer(sf::microseconds(0))
{
}

/// <summary>
/// Initialise le projectile.
/// Doit être appelé une fois avant l'utilisation du projectile.
/// </summary>
/// <param name="spriteKey">La clé de sprite qui sera utilisé par le projectile.</param>
void EnergyBall::init(RessourceManager::key spriteKey)
{
	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(ENERGY_BALL_WIDTH / 2, ENERGY_BALL_HEIGHT / 2);
	setDimension(ENERGY_BALL_WIDTH, ENERGY_BALL_HEIGHT);
}

/// <summary>
/// Active le projectile.
/// </summary>
/// <param name="position">La position à laquelle activer le projectile.</param>
/// <param name="color">La couleur avec laquelle activer le projectile.</param>
void EnergyBall::activate(const sf::Vector2f& position, const sf::Color& color)
{
	moveTimer = sf::microseconds(0);
	EnemyProjectile::activate(position, color);
}

/// <summary>
/// Met à jour l'EnergyBall.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel d'update.</param>
void EnergyBall::update(const float deltaT)
{
	if (isActivated())
	{
		moveTimer += sf::seconds(deltaT);
		if (moveTimer.asMilliseconds() >= MS_BEFORE_MOVE)
		{
			EnemyProjectile::update(deltaT);
		}
	}
}