#include "TwistedShooterAdder.h"

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="TwistedShooterAdder"/>.
/// </summary>
TwistedShooterAdder::TwistedShooterAdder()
	:WeaponAdder(GameObject::ObjectType::TWISTED_SHOOTER_ADDER, Weapon::WeaponType::TWISTED_SHOOTER)
{
}