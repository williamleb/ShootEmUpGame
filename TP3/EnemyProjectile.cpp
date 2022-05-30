#include "EnemyProjectile.h"
#include "RessourceManager.h"
#include <cassert>

using namespace TP3;

/// <summary>
/// crée un nouveau <see cref="EnemyProjectile"/>.
/// </summary>
/// <param name="type">Le type du projectile.</param>
/// <param name="speed">La vitesse du projectile.</param>
/// <param name="power">Les dégâts infligés par le projectile.</param>
/// <param name="health">La vie du projectile.</param>
EnemyProjectile::EnemyProjectile(const ObjectType type, const float speed, const int power, const unsigned int health)
	: Projectile(type, speed, power, health, ProjectileFaction::ENEMY), color(sf::Color::White)
{
	assert(isEnemyProjectile(type) && "Le type doit en être un de projectile d'ennemi.");
}

/// <summary>
/// Endommage le projectile.
/// </summary>
/// <param name="life">Le nombre de dégâts subits par le projectile.</param>
void EnemyProjectile::damage(const unsigned int life)
{
	Projectile::damage(life);

	if (isDestroyed())
	{
		deactivate();
	}
}

/// <summary>
/// Endommage le projectile.
/// </summary>
/// <param name="life">Le nombre de dégâts subits par le projectile.</param>
/// <param name="dammageColor">La couleur du dommage subit par le projectile.</param>
void EnemyProjectile::damage(const unsigned int life, const sf::Color& dammageColor)
{
	// Endommage le projectile seulement si la couleur de ce qui a fait le dommage n'est pas la même que la sienne.
	if (dammageColor != this->color)
	{
		this->damage(life);
	}
}

/// <summary>
/// Retourne la couleur du projectile.
/// </summary>
/// <returns>La couleur du projectile.</returns>
const sf::Color& EnemyProjectile::getColor()
{
	return color;
}

/// <summary>
/// Active le projectile.
/// </summary>
/// <param name="position">La position à laquelle activer le projectile.</param>
/// <param name="color">La couleur avec laquelle activer le projectile.</param>
void EnemyProjectile::activate(const sf::Vector2f& position, const sf::Color& color)
{
	Projectile::activate(position);
	this->color = color;
}

/// <summary>
/// Affiche le projectile.
/// </summary>
/// <param name="window">La fenêtre sur laquelle afficher le projectile.</param>
void EnemyProjectile::draw(sf::RenderWindow& window)
{
	RessourceManager::getInstance()->getSprite(getSpriteKey())->setColor(color);
	Projectile::draw(window);
}