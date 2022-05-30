#include "FollowedCargo.h"
#include "GameScene.h"

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="FollowedCargo"/>.
/// </summary>
FollowedCargo::FollowedCargo()
	: Cargo(GameObject::ObjectType::FOLLOWED_CARGO, FOLLOWED_CARGO_SPAWN_RATE)
{
}

/// <summary>
/// Fait apparaître un nouveau Followed.
/// </summary>
void FollowedCargo::spawn()
{
	if (isActivated() && !isDestroyed())
	{
		getGameScene()->activateObject(GameObject::ObjectType::FOLLOWED, getPosition() - sf::Vector2f(getDimension().x, 0) * 0.5f);
	}
}