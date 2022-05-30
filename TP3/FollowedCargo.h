#pragma once

#include "Cargo.h"

namespace TP3
{	
	/// <summary>
	/// Cargo qui fait apparaître des ennemis de type Followed.
	/// </summary>
	/// <seealso cref="Cargo" />
	class FollowedCargo : public Cargo
	{
		static const int FOLLOWED_CARGO_SPAWN_RATE = 750;

	public:
		FollowedCargo();

		void spawn();
	};
}