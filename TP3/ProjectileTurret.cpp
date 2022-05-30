#include "ProjectileTurret.h"
#include "GameScene.h"
using namespace TP3;


/// <summary>
/// Crée un nouveau <see cref="Projectile"/>.
/// </summary>
ProjectileTurret::ProjectileTurret()
	:EnemyProjectile(GameObject::PROJECTILE_TURRET, PROJECTILE_SPEED)
{
	setDimension(PROJECTILE_WIDTH, PROJECTILE_HEIGHT);
}

/// <summary>
/// Crée un nouveau <see cref="Projectile"/>.
/// </summary>
/// <param name="direction">La direction du projectile.</param>
ProjectileTurret::ProjectileTurret(Direction direction, const sf::Vector2f& position)
	:EnemyProjectile(GameObject::PROJECTILE_TURRET, PROJECTILE_SPEED)
{
	setDimension(PROJECTILE_WIDTH, PROJECTILE_HEIGHT);
	setPosition(position);


}

void ProjectileTurret::draw(sf::RenderWindow & window)
{
	if (isActivated())
	{
		EnemyProjectile::draw(window);
	}
}

/// <summary>
/// Initialise tous les projectiles.
/// Doit être appelé avant d'instancier un projectile.
/// </summary>
/// <param name="spriteKey">La clé de sprite qui sera utilisé par tous les projectiles.</param>
void ProjectileTurret::init(RessourceManager::key spriteKey)
{
	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(PROJECTILE_WIDTH / 2, PROJECTILE_HEIGHT / 2);
}

/// <summary>
/// Met à jour le projectile.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la méthode.</param>
void ProjectileTurret::update(const float deltaT)
{
	if (isActivated())
	{
		EnemyProjectile::update(deltaT);
	}

}

/// <summary>
/// Active le projectile de la tourette.
/// </summary>
/// <param name="position">La position avec laquelle activer le projectile.</param>
void ProjectileTurret::activate(const sf::Vector2f& position)
{
	setPosition(position);
	Activatable::activate();
}

/// <summary>
/// Change la direction du projectile.
/// </summary>
/// <param name="angle">La direction du projectile (en radians).</param>
void ProjectileTurret::setDirection(const float angle)
{
	setDirection(Movable::convertDirection(angle));
}

/// <summary>
/// Change la direction du projectile.
/// </summary>
/// <param name="direction">La direction du projectile.</param>
void ProjectileTurret::setDirection(const Direction direction)
{
	sf::Sprite* sprite = RessourceManager::getInstance()->operator[](getSpriteKey());
	setDirection(Movable::convertDirection(direction));
	sprite->setRotation(direction);
}

/// <summary>
/// Change la direction du projectile.
/// </summary>
/// <param name="direction">La direction du projectile.</param>
void ProjectileTurret::setDirection(sf::Vector2f direction)
{
	Movable::setDirection(direction);
}
