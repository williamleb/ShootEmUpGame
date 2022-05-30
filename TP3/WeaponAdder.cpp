#include "WeaponAdder.h"

using namespace TP3;

/// <summary>
/// Cr�e un nouveau <see cref="WeaponAdder"/>.
/// </summary>
/// <param name="type">Le type de WeaponAdder.</param>
/// <param name="weaponType">Le type d'arme ajout� par le bonus.</param>
WeaponAdder::WeaponAdder(const GameObject::ObjectType type, const Weapon::WeaponType weaponType)
	:Bonus(type), weaponType(weaponType)
{
}

/// <summary>
/// D�truit un <see cref="WeaponAdder"/>.
/// </summary>
WeaponAdder::~WeaponAdder()
{
}

/// <summary>
/// Retourne le type d'arme ajout� par le bonus.
/// </summary>
/// <returns>Le type d'arme ajout� par le bonus.</returns>
Weapon::WeaponType WeaponAdder::getWeapon() const
{
	return weaponType;
}