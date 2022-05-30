#include "TriShooter.h"
#include "GameScene.h"

using namespace TP3;

const float TriShooter::ANGLE_1 = -M_PI_4;
const float TriShooter::ANGLE_2 = M_PI_4;

/// <summary>
/// Crée un nouveau <see cref="TriShooter"/>.
/// </summary>
TriShooter::TriShooter()
	:Weapon(WeaponType::TRI_SHOOTER, TRI_SHOOTER_FIRE_DELAY, TRI_SHOOTER_MAX_AMMO)
{
	addAmmo(INFINITE_AMMO);
}

/// <summary>
/// Tire avec l'arme.
/// </summary>
void TriShooter::fire()
{
	GameScene* game = getGameScene();

	if (tryFire())
	{
		// TODO: Changer la position d'appaition.
		if (game->activateMovable(GameObject::PLASMA_BALL, getPlayer()->getPosition(), ANGLE_1))
		{
			loseAmmo();
		}

		if (game->activateMovable(GameObject::PLASMA_BALL, getPlayer()->getPosition(), Movable::RIGHT))
		{
			loseAmmo();
		}

		if (game->activateMovable(GameObject::PLASMA_BALL, getPlayer()->getPosition(), ANGLE_2))
		{
			loseAmmo();
		}
	}

	// Ne perd pas de munitions (parce qu'il en a une infinité).
}



