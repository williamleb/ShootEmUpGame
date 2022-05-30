#pragma once
#include "Projectile.h"

namespace TP3
{
	/// <summary>
	/// Crée un projectile allié de type Slash.
	/// Le Slash est fait en ligne verticale et va en ligne droite.
	/// </summary>
	/// <seealso cref="Projectile" />
	class Slash : public Projectile
	{
	private:
		static const int SLASH_SPEED = 600;
		static const int SLASH_POWER = 3;
		static const int SLASH_HEALTH = 3;

		static const int SLASH_WIDTH = 26;
		static const int SLASH_HEIGHT = 128;

	public:
		Slash();
		void init(RessourceManager::key spriteKey);
	};
}