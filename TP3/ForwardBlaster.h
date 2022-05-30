#pragma once

#include "Weapon.h"

namespace TP3
{	
	/// <summary>
	/// Le forward blaster est une arme de base (elle a une infinité de munitions).
	/// Elle fait un tir par l'avant.
	/// </summary>
	/// <seealso cref="Weapon" />
	class ForwardBlaster : public Weapon
	{
		static const int FORWARD_BLASTER_MAX_AMMO = Weapon::INFINITE_AMMO;
		static const int FORWARD_BLASTER_FIRE_DELAY = 150;
		static const int FORWARD_BLASTER_DEFAULT_AMMO = Weapon::INFINITE_AMMO;

	public:		
		ForwardBlaster();

		void fire();
		
	};
}