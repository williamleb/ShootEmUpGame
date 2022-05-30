#pragma once

#include "Bonus.h"

namespace TP3
{	
	/// <summary>
	/// Une bombe �lectromagn�tique.
	/// Lorsqu'elle est ramass�e par le joueur, elle emp�che les ennemis de tirer pendant quelques secondes.
	/// Lorsqu'elle est ramass�e par un ennemi, elle emp�che le joueur de tirer pendant quelques secondes.
	/// </summary>
	/// <seealso cref="Bonus" />
	class ElectroBomb : public Bonus
	{
	public:		
		ElectroBomb();

		static const int MS_OF_DISABILITY = 5000;
	};
}
