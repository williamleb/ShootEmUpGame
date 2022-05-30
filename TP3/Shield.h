#pragma once
#include "Destroyable.h"
#include "Sujet.h"
#include <SFML/Graphics.hpp>

namespace TP3
{	
	/// <summary>
	/// Représente un des boucliers du joueur.
	/// </summary>
	/// <seealso cref="Destroyable" />
	/// <seealso cref="Sujet" />
	class Shield : public Destroyable, public Sujet
	{
		sf::Color color;
	public:		
		Shield(const sf::Color& color);

		const sf::Color& getColor() const;

		void damage(const unsigned int life, const sf::Color& dammageColor);
	};
}