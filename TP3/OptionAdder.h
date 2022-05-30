#pragma once

#include "Bonus.h"

namespace TP3
{
	/// <summary>
	/// Bonus qui ajoute une option qui aide le joueur.
	/// </summary>
	/// <seealso cref="Bonus" />
	class OptionAdder : public Bonus
	{
		sf::Color color;

	public:		
		OptionAdder();
	};
}
