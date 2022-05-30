#pragma once

#include <SFML/System.hpp>

namespace TP3
{	
	/// <summary>
	/// Repr�sente un objet qui peut �tre activ� ou d�sactiv� dans le jeu.
	/// </summary>
	class Activatable
	{
		bool activated;

	public:
		Activatable();

		virtual void activate();
		virtual void activate(const sf::Vector2f& position) = 0;
		virtual void deactivate();

		bool isActivated() const;
	};
}