#include "DoubleBlaster.h"
#include "GameScene.h"

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="DoubleBlaster"/>.
/// </summary>
DoubleBlaster::DoubleBlaster()
	:Weapon(WeaponType::DOUBLE_BLASTER, DOUBLE_BLASTER_FIRE_DELAY, DOUBLE_BLASTER_MAX_AMMO)
{
	addAmmo(INFINITE_AMMO);
}

/// <summary>
/// Tire avec l'arme.
/// </summary>
void DoubleBlaster::fire()
{
	GameScene* game = getGameScene();

	if (tryFire())
	{
		if (game->activateMovable(GameObject::BEAM, getPlayer()->getPosition() + sf::Vector2f(0, -5), Movable::RIGHT))
		{
			loseAmmo();
		}

		if (game->activateMovable(GameObject::BEAM, getPlayer()->getPosition() + sf::Vector2f(0, 5), Movable::RIGHT))
		{
			loseAmmo();
		}
	}
}



