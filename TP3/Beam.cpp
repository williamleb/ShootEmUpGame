#include "Beam.h"
#include "RessourceManager.h"


using namespace TP3;

/// <summary>
/// crée un nouveau <see cref="Beam"/>.
/// </summary>
Beam::Beam()
	: Projectile(GameObject::BEAM, BEAM_SPEED, BEAM_POWER, BEAM_HEALTH, ProjectileFaction::PLAYER)
{
}

/// <summary>
/// Initialise le projectile.
/// Doit être appelé une fois avant l'utilisation.
/// </summary>
/// <param name="spriteKey">La clé de sprite du projecile.</param>
void Beam::init(RessourceManager::key spriteKey)
{
	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(BEAM_WIDTH / 2, BEAM_HEIGHT / 2);
	setDimension(BEAM_WIDTH, BEAM_HEIGHT);
}
