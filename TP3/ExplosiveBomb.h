#pragma once

#include "Bonus.h"

namespace TP3
{	
	/// <summary>
	/// La bombe explosive.
	/// Fait plus de dommage lorsque les objets sont plus proche.
	/// Ne fait pas de dommage aux entités de la même couleur.
	/// </summary>
	/// <seealso cref="Bonus" />
	class ExplosiveBomb : public Bonus
	{
		sf::Color color;

	public:		
		ExplosiveBomb();

		const sf::Color& getColor() const;

		void draw(sf::RenderWindow& window);

		static const int MAX_DAMAGE = 15;
	};
}
