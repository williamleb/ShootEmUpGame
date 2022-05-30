#pragma once

#include "Cargo.h"

namespace TP3
{	
	/// <summary>
	/// Cargo qui fait appara�tre des ennemis de type Trooper.
	/// </summary>
	/// <seealso cref="Cargo" />
	class TrooperCargo : public Cargo
	{
		static const int TROOPER_CARGO_SPAWN_RATE = 750;

	public:		
		TrooperCargo();

		void spawn();
	};
}