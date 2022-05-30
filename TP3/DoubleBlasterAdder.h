#pragma once

#include "WeaponAdder.h"

namespace TP3
{	
	/// <summary>
	/// Bonus qui ajoute un Double Blaster � la liste des armes du joueur.
	/// </summary>
	/// <seealso cref="WeaponAdder" />
	class DoubleBlasterAdder : public WeaponAdder
	{
	public:
		DoubleBlasterAdder();
	};
}