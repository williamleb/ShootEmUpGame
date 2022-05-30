#include "Background.h"
#include "GameScene.h"
#include <cassert>

using namespace TP3;


/// <summary>
/// Crée un nouveau <see cref="Background"/>.
/// </summary>
Background::Background(const unsigned int layer, const unsigned int position, const RessourceManager::key spriteKey)
	: Movable(GameObject::BACKGROUND)
{
	assert(layer == 1 || layer == 2 || layer == 3 && "La valeur de layer doit être 1, 2 ou 3.");
	assert(position == 1 || position == 2 && "La position doit être 1 ou 2.");

	setSpriteKey(spriteKey);

	float speedMultiplicator = 0.0f;
	switch (layer)
	{
	case 1:
		speedMultiplicator = 0.75f;
		break;
	case 2:
		speedMultiplicator = 0.5f;
		break;
	case 3:
		speedMultiplicator = 0.25f;
		break;
	}
	setDirection(LEFT);
	setSpeed(GameScene::SCROLLING_SPEED * speedMultiplicator);

	if (position == 1)
	{
		setPosition(GameScene::GAME_LEFT, GameScene::GAME_TOP);
	}
	else
	{
		setPosition(GameScene::GAME_LEFT + BACKGROUND_WIDTH, GameScene::GAME_TOP);
	}
}

/// <summary>
/// Update l'objet selon le temps écoulé.
/// Le background défile moins vite s'il est plus loin.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la méthode.</param>
void Background::update(const float deltaT)
{
	Movable::update(deltaT);

	if (getPosition().x <= -BACKGROUND_WIDTH + GameScene::GAME_LEFT)
	{
		setPosition(2 * BACKGROUND_WIDTH + getPosition().x + GameScene::GAME_LEFT, GameScene::GAME_TOP);
	}
}