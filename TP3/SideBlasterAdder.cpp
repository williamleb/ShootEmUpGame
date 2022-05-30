#include "SideBlasterAdder.h"

using namespace TP3;

/// <summary>
/// Cr�e un nouveau <see cref="SideBlasterAdder"/>.
/// </summary>
SideBlasterAdder::SideBlasterAdder()
	:WeaponAdder(GameObject::ObjectType::SIDE_BLASTER_ADDER, Weapon::WeaponType::SIDE_BLASTER)
{
}