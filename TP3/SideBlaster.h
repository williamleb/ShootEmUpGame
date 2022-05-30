#pragma once

#include "Weapon.h"

namespace TP3
{	
	/// <summary>
	/// Le side blaster est une arme spéciale.
	/// Elle fait un tir vers le haut, un tir vers le bas et un tir vers l'arrière.
	/// </summary>
	/// <seealso cref="Weapon" />
	class SideBlaster : public Weapon
	{
		static const int SIDE_BLASTER_MAX_AMMO = 300;
		static const int SIDE_BLASTER_FIRE_DELAY = 130;
		static const int FORWARD_BLASTER_DEFAULT_AMMO = 75;

	public:		
		SideBlaster();

		void fire();
	};
}
