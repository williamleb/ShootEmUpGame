#include "Stalker.h"
#include "GameScene.h"

using namespace TP3;

/// <summary>
/// Cr�e un nouveau <see cref="Stalker"/>.
/// </summary>
Stalker::Stalker()
	: Enemy(ObjectType::STALKER, STALKER_FIRERATE, STALKER_DEFAULT_LIFE, STALKER_DEFAULT_SPEED, STALKER_POINTS, STALKER_COLLISION_DAMAGE)
{
}

/// <summary>
/// Update l'ennemi selon le temps �coul�.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la m�thode.</param>
void Stalker::update(const float deltaT)
{
	Enemy::update(deltaT);
	if (getState() == Moving)
	{
		setPosition(std::max(getPosition().x, GameScene::GAME_LEFT + GameScene::GAME_WIDTH * 0.5f), getPlayer()->getPosition().y);
	}
}

/// <summary>
/// Initialise le Stalker.
/// Doit �tre appel� une fois avant d'utiliser l'ennemi.
/// </summary>
/// <param name="spriteKey">Le sprite du Follower.</param>
/// <returns>true si l'initialisation s'est bien pass�e; false sinon.</returns>
bool Stalker::init(const RessourceManager::key spriteKey)
{
	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(STALKER_WIDTH / 2, STALKER_HEIGHT / 2);
	setDimension(STALKER_WIDTH, STALKER_HEIGHT);

	return true;
}

/// <summary>
/// Fait tirer l'ennemi.
/// </summary>
void Stalker::fire()
{
	GameScene* gameScene = getGameScene();
	gameScene->activateEnemyProjectile(ObjectType::LAZER, this, Direction::LEFT,
		getPosition() - sf::Vector2f(getDimension().x * 0.5f, 10));
	gameScene->activateEnemyProjectile(ObjectType::LAZER, this, Direction::LEFT,
		getPosition() - sf::Vector2f(getDimension().x * 0.5f, -10));
}