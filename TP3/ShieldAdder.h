#pragma once

#include "Bonus.h"

namespace TP3
{	
	/// <summary>
	/// Bonus qui ajoute un bouclier au joueur.
	/// </summary>
	/// <seealso cref="Bonus" />
	class ShieldAdder : public Bonus
	{
		sf::Color color;

	public:		
		ShieldAdder();

		const sf::Color& getColor() const;

		void draw(sf::RenderWindow& window);
	};
}