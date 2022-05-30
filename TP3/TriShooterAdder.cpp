#include "TriShooterAdder.h"

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="TriShooterAdder"/>.
/// </summary>
TriShooterAdder::TriShooterAdder()
	:WeaponAdder(GameObject::ObjectType::TRI_SHOOTER_ADDER, Weapon::WeaponType::TRI_SHOOTER)
{
}