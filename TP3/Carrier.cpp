#include "Carrier.h"
#include "GameScene.h"

using namespace TP3;

/// <summary>
/// Cr�e un nouveau <see cref="Carrier"/>.
/// </summary>
Carrier::Carrier()
	: Enemy(ObjectType::CARRIER, CARRIER_FIRERATE, CARRIER_DEFAULT_LIFE, CARRIER_DEFAULT_SPEED, CARRIER_POINTS, CARRIER_COLLISION_DAMAGE)
{
}

/// <summary>
/// Update l'ennemi selon le temps �coul�.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la m�thode.</param>
void Carrier::update(const float deltaT)
{
	Enemy::update(deltaT);
}

/// <summary>
/// Initialise le Carriers.
/// Doit �tre appel� une fois avant d'utiliser l'ennemi.
/// </summary>
/// <param name="spriteKey">Le sprite du Follower.</param>
/// <returns>true si l'initialisation s'est bien pass�e; false sinon.</returns>
bool Carrier::init(const RessourceManager::key spriteKey)
{
	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(CARRIER_WIDTH / 2, CARRIER_HEIGHT / 2);
	setDimension(CARRIER_WIDTH, CARRIER_HEIGHT);

	return true;
}

/// <summary>
/// Fait tirer l'ennemi.
/// </summary>
void Carrier::fire()
{
	// Le Carrier ne fait pas feu.
}