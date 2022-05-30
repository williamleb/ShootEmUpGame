#pragma once

#include "Bonus.h"

namespace TP3
{	
	/// <summary>
	/// Une bombe électromagnétique.
	/// Lorsqu'elle est ramassée par le joueur, elle empêche les ennemis de tirer pendant quelques secondes.
	/// Lorsqu'elle est ramassée par un ennemi, elle empêche le joueur de tirer pendant quelques secondes.
	/// </summary>
	/// <seealso cref="Bonus" />
	class ElectroBomb : public Bonus
	{
	public:		
		ElectroBomb();

		static const int MS_OF_DISABILITY = 5000;
	};
}
