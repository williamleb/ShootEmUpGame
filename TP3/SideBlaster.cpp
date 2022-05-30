#include "SideBlaster.h"
#include "GameScene.h"

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="SideBlaster"/>.
/// </summary>
SideBlaster::SideBlaster()
	:Weapon(WeaponType::SIDE_BLASTER, SIDE_BLASTER_FIRE_DELAY, SIDE_BLASTER_MAX_AMMO)
{
	addAmmo(INFINITE_AMMO );
}

/// <summary>
/// Tire avec l'arme.
/// </summary>
void SideBlaster::fire()
{
	GameScene* game = getGameScene();

	if (tryFire())
	{
		// TODO: Changer la position d'apparition et les munitions.
		Player* player = getPlayer();
		if (game->activateMovable(GameObject::PLASMA_BALL, player->getPosition() + sf::Vector2f(-player->getDimension().x, -player->getDimension().y) * 0.5f, Movable::UP))
		{
			loseAmmo();
		}

		if (game->activateMovable(GameObject::BEAM, player->getPosition() + sf::Vector2f(-player->getDimension().x, 0), Movable::LEFT))
		{
			loseAmmo();
		}

		if (game->activateMovable(GameObject::PLASMA_BALL, player->getPosition() + sf::Vector2f(-player->getDimension().x, player->getDimension().y) * 0.5f, Movable::DOWN))
		{
			loseAmmo();
		}
	}

	// Ne perd pas de munitions (parce qu'il en a une infinité).
}