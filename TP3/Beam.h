#pragma once
#include "Projectile.h"

namespace TP3
{
	/// <summary>
	/// Crée un projectile allié de type Beam.
	/// Le Beam est fait en ligne et va en ligne droite.
	/// </summary>
	/// <seealso cref="Projectile" />
	class Beam : public Projectile
	{
	private:
		static const int BEAM_SPEED = 750;
		static const int BEAM_POWER = 1;
		static const int BEAM_HEALTH = 3;

		static const int BEAM_WIDTH = 96;
		static const int BEAM_HEIGHT = 16;

	public:
		Beam();
		void init(RessourceManager::key spriteKey);
	};
}