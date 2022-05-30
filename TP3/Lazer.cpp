#include "Lazer.h"
#include "GameScene.h"
using namespace TP3;


/// <summary>
/// Cr�e un nouveau <see cref="Projectile"/>.
/// </summary>
Lazer::Lazer()
	:EnemyProjectile(GameObject::LAZER, LAZER_SPEED, LAZER_POWER, LAZER_HEALTH)
{
}

/// <summary>
/// Initialise le projectile.
/// Doit �tre appel� une fois avant l'utilisation du projectile.
/// </summary>
/// <param name="spriteKey">La cl� de sprite qui sera utilis� par le projectile.</param>
void Lazer::init(RessourceManager::key spriteKey)
{
	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(LAZER_WIDTH / 2, LAZER_HEIGHT / 2);
	setDimension(LAZER_WIDTH, LAZER_HEIGHT);
}
