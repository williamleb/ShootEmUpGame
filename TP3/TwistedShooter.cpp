#include "TwistedShooter.h"
#include "GameScene.h"

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="TwistedShooter"/>.
/// </summary>
TwistedShooter::TwistedShooter()
	:Weapon(WeaponType::TWISTED_SHOOTER, TWISTED_SHOOTER_FIRE_DELAY, TWISTED_SHOOTER_MAX_AMMO)
{
	addAmmo(INFINITE_AMMO);
}

/// <summary>
/// Tire avec l'arme.
/// </summary>
void TwistedShooter::fire()
{
	GameScene* game = getGameScene();

	if (tryFire())
	{
		if (game->activateMovable(GameObject::TWIST, getPlayer()->getPosition(), Movable::RIGHT))
		{
			loseAmmo();
		}
	}
}
