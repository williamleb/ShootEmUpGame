#include "Slash.h"
#include "RessourceManager.h"


using namespace TP3;

/// <summary>
/// cr�e un nouveau <see cref="Slash"/>.
/// </summary>
Slash::Slash()
	: Projectile(GameObject::SLASH, SLASH_SPEED, SLASH_POWER, SLASH_HEALTH, ProjectileFaction::PLAYER)
{
}

/// <summary>
/// Initialise le projectile.
/// Doit �tre appel� une fois avant l'utilisation.
/// </summary>
/// <param name="spriteKey">La cl� de sprite du projecile.</param>
void Slash::init(RessourceManager::key spriteKey)
{
	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(SLASH_WIDTH / 2, SLASH_HEIGHT / 2);
	setDimension(SLASH_WIDTH, SLASH_HEIGHT);
}
