#include "RedLazer.h"
using namespace TP3;
RedLazer::RedLazer()
	:EnemyProjectile(GameObject::RED_LAZER,SPEED)
{
	setDimension(PROJECTILE_WIDTH, PROJECTILE_HEIGHT);
}

void RedLazer::init(RessourceManager::key spriteKey)
{

	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(PROJECTILE_WIDTH / 2, PROJECTILE_HEIGHT / 2);
}
