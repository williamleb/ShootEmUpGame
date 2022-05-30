#pragma once

#include "Weapon.h"

namespace TP3
{
	/// <summary>
	/// Le forward blaster est une arme spéciale.
	/// Elle fait deux tirs vers l'avant.
	/// </summary>
	/// <seealso cref="Weapon" />
	class DoubleBlaster : public Weapon
	{
		static const int DOUBLE_BLASTER_MAX_AMMO = 100;
		static const int DOUBLE_BLASTER_FIRE_DELAY = 150;
		static const int DOUBLE_BLASTER_DEFAULT_AMMO = 25;

	public:
		DoubleBlaster();

		void fire();

	};
}