#include "Slasher.h"
#include "GameScene.h"

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="Slasher"/>.
/// </summary>
Slasher::Slasher()
	:Weapon(WeaponType::SLASHER, SLASHER_FIRE_DELAY, SLASHER_MAX_AMMO)
{
	addAmmo(INFINITE_AMMO);
}

/// <summary>
/// Tire avec l'arme.
/// </summary>
void Slasher::fire()
{
	GameScene* game = getGameScene();

	if (tryFire())
	{
		if (game->activateMovable(GameObject::SLASH, getPlayer()->getPosition(), Movable::RIGHT))
		{
			loseAmmo();
		}
	}

}
