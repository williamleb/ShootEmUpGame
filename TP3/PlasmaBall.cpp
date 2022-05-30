#include "PlasmaBall.h"
#include "RessourceManager.h"


using namespace TP3;

/// <summary>
/// cr�e un nouveau <see cref="PlasmaBall"/>.
/// </summary>
PlasmaBall::PlasmaBall()
	: Projectile(GameObject::PLASMA_BALL, PLASMA_BALL_SPEED, PLASMA_BALL_POWER, PLASMA_BALL_HEALTH, ProjectileFaction::PLAYER)
{
}

/// <summary>
/// Initialise le projectile.
/// Doit �tre appel� une fois avant l'utilisation.
/// </summary>
/// <param name="spriteKey">La cl� de sprite du projecile.</param>
void PlasmaBall::init(RessourceManager::key spriteKey)
{
	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(PLASMA_BALL_WIDTH / 2, PLASMA_BALL_HEIGHT / 2);
	setDimension(PLASMA_BALL_WIDTH, PLASMA_BALL_HEIGHT);
}
