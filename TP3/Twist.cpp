#define _USE_MATH_DEFINES

#include <cmath>
#include "Twist.h"
#include "RessourceManager.h"

using namespace TP3;

const float Twist::WAVE_SPEED = 2 * M_PI;

/// <summary>
/// cr�e un nouveau <see cref="Twist"/>.
/// </summary>
Twist::Twist()
	: Projectile(GameObject::TWIST, TWIST_SPEED, TWIST_POWER, TWIST_HEALTH, ProjectileFaction::PLAYER)
{
	waveX = rand() % 6;
}

/// <summary>
/// Initialise le projectile.
/// Doit �tre appel� une fois avant l'utilisation.
/// </summary>
/// <param name="spriteKey">La cl� de sprite du projecile.</param>
void Twist::init(RessourceManager::key spriteKey)
{
	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(TWIST_WIDTH / 2, TWIST_HEIGHT / 2);
	setDimension(TWIST_WIDTH, TWIST_HEIGHT);
}

/// <summary>
/// Update le projectile selon le temps �coul�.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la m�thode.</param>
void Twist::update(const float deltaT)
{
	if (isActivated())
	{
		setPosition(getPosition().x, posY);
		Projectile::update(deltaT);

		waveX += WAVE_SPEED * deltaT;

		setPosition(getPosition().x, posY + std::sinf(waveX) * AMPLITUDE);
	}
}

/// <summary>
/// Active le projectile.
/// </summary>
/// <param name="position">La position � laquelle activer le projectile.</param>
void Twist::activate(const sf::Vector2f& position)
{
	posY = position.y;

	Projectile::activate(position);
}