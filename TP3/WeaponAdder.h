#pragma once

#include "Bonus.h"
#include "Weapon.h"

namespace TP3
{	
	/// <summary>
	/// On bonus qui donne une nouvelle arme au joueur.
	/// </summary>
	/// <seealso cref="Bonus" />
	class WeaponAdder : public Bonus
	{
		Weapon::WeaponType weaponType;

	public:		
		virtual ~WeaponAdder();

		Weapon::WeaponType getWeapon() const;

	protected:		
		WeaponAdder(const GameObject::ObjectType type, const Weapon::WeaponType weaponType);
	};
}