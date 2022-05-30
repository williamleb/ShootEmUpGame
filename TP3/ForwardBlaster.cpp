#include "ForwardBlaster.h"
#include "GameScene.h"

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="ForwardBlaster"/>.
/// </summary>
ForwardBlaster::ForwardBlaster()
	:Weapon(WeaponType::FORWARD_BLASTER, FORWARD_BLASTER_FIRE_DELAY, FORWARD_BLASTER_MAX_AMMO)
{
	addAmmo(INFINITE_AMMO);
}

/// <summary>
/// Tire avec l'arme.
/// </summary>
void ForwardBlaster::fire()
{
	GameScene* game = getGameScene();

	if (tryFire())
	{
		game->activateMovable(GameObject::BEAM, getPlayer()->getPosition(), Movable::RIGHT);
	}

	// Ne perd pas de munitions (parce qu'il en a une infinité).
}
