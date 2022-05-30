#pragma once

#include <SFML/System.hpp>

namespace TP3
{	
	/// <summary>
	/// Représente un objet qui peut être activé ou désactivé dans le jeu.
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