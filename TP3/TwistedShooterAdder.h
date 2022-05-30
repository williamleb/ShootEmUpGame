#pragma once

#include "WeaponAdder.h"

namespace TP3
{
	/// <summary>
	/// Bonus qui ajoute un Twisted Shooter à la liste des armes du joueur.
	/// </summary>
	/// <seealso cref="WeaponAdder" />
	class TwistedShooterAdder : public WeaponAdder
	{
	public:
		TwistedShooterAdder();
	};
}