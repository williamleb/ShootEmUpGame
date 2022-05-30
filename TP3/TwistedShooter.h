#pragma once

#include "Weapon.h"

namespace TP3
{
	/// <summary>
	/// Le forward blaster est une arme de base (elle a une infinité de munitions).
	/// Elle fait un tir par l'avant.
	/// </summary>
	/// <seealso cref="Weapon" />
	class TwistedShooter : public Weapon
	{
		static const int TWISTED_SHOOTER_MAX_AMMO = 150;
		static const int TWISTED_SHOOTER_FIRE_DELAY = 110;
		static const int TWISTED_SHOOTER_DEFAULT_AMMO = 30;

	public:
		TwistedShooter();

		void fire();

	};
}
