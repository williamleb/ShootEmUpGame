#include "DoubleBlasterAdder.h"

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="DoubleBlasterAdder"/>.
/// </summary>
DoubleBlasterAdder::DoubleBlasterAdder()
	: WeaponAdder(GameObject::ObjectType::DOUBLE_BLASTER_ADDER, Weapon::WeaponType::DOUBLE_BLASTER)
{
}