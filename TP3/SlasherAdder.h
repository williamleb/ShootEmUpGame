#pragma once

#include "WeaponAdder.h"

namespace TP3
{
	/// <summary>
	/// Bonus qui ajoute un Slasher à la liste des armes du joueur.
	/// </summary>
	/// <seealso cref="WeaponAdder" />
	class SlasherAdder : public WeaponAdder
	{
	public:
		SlasherAdder();
	};
}