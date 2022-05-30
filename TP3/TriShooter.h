#pragma once

#include "Weapon.h"

namespace TP3
{
	/// <summary>
	/// Le forward blaster est une arme spéciale.
	/// Elle fait trois tir par l'avant avec un angle différent pour chaque tir.
	/// </summary>
	/// <seealso cref="Weapon" />
	class TriShooter : public Weapon
	{
		static const int TRI_SHOOTER_MAX_AMMO = 200;
		static const int TRI_SHOOTER_FIRE_DELAY = 100;
		static const int TRI_SHOOTER_DEFAULT_AMMO = 75;

		static const float ANGLE_1;
		static const float ANGLE_2;

	public:
		TriShooter();

		void fire();

	};
}