#include "TrooperCargo.h"
#include "GameScene.h"

using namespace TP3;

/// <summary>
/// Cr�e un nouveau <see cref="TrooperCargo"/>.
/// </summary>
TrooperCargo::TrooperCargo()
	: Cargo(GameObject::ObjectType::TROOPER_CARGO, TROOPER_CARGO_SPAWN_RATE)
{
}

/// <summary>
/// Fait appara�tre un nouveau Trooper.
/// </summary>
void TrooperCargo::spawn()
{
	if (isActivated() && !isDestroyed())
	{
		getGameScene()->activateObject(GameObject::ObjectType::TROOPER, getPosition() - sf::Vector2f(getDimension().x, 0) * 0.5f);
	}
}