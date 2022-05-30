#pragma once

#include "Bonus.h"

namespace TP3
{	
	/// <summary>
	/// Multiplicateur de points.
	/// Ajoute un multiplicateur de points pendant quelques secondes.
	/// </summary>
	/// <seealso cref="Bonus" />
	class PointsMultiplicator : public Bonus
	{

	public:		
		PointsMultiplicator();

		static const int MS_OF_MULTIPLICATION = 30000;
	};
}
