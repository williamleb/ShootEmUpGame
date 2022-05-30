#pragma once

#include "WeaponAdder.h"

namespace TP3
{
	/// <summary>
	/// Bonus qui ajoute un Side Blaster à la liste des armes du joueur.
	/// </summary>
	/// <seealso cref="WeaponAdder" />
	class SideBlasterAdder : public WeaponAdder
	{
	public:
		SideBlasterAdder();
	};
}