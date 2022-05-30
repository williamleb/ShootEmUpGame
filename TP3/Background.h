#pragma once

#include "Movable.h"
#include "RessourceManager.h"

namespace TP3
{	
	/// <summary>
	/// Une image de fond qui bouge moins vite que le décor.
	/// </summary>
	/// <seealso cref="Movable" />
	class Background : public Movable
	{
		static const int BACKGROUND_WIDTH = 1400;
		static const int BACKGROUND_HEIGHT = 700;

	public:
		Background(const unsigned int layer, const unsigned int position, const RessourceManager::key spriteKey);

		void update(const float deltaT);
	};
}