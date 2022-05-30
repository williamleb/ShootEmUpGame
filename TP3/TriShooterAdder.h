#pragma once

#include "WeaponAdder.h"

namespace TP3
{
	/// <summary>
	/// Bonus qui ajoute un Tri Shooter à la liste des armes du joueur.
	/// </summary>
	/// <seealso cref="WeaponAdder" />
	class TriShooterAdder : public WeaponAdder
	{
	public:
		TriShooterAdder();
	};
}