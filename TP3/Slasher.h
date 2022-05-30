#pragma once

#include "Weapon.h"

namespace TP3
{
	/// <summary>
	/// Le forward blaster est une arme de base (elle a une infinité de munitions).
	/// Elle fait un tir par l'avant.
	/// </summary>
	/// <seealso cref="Weapon" />
	class Slasher : public Weapon
	{
		static const int SLASHER_MAX_AMMO = 50;
		static const int SLASHER_FIRE_DELAY = 400;
		static const int SLASHER_DEFAULT_AMMO = 10;

	public:
		Slasher();

		void fire();

	};
}