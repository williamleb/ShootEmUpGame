#pragma once

#include <SFML/Graphics.hpp>

namespace TP3
{
	/// <summary>
	/// Repr�sente le jeu.
	/// </summary>
	class Game
	{
	public:		
		Game();
		int run();

	private:
		const int WINDOW_WIDTH = 1280;
		const int WINDOW_HEIGHT = 1000;

		sf::RenderWindow mainWin;
		sf::Event event;
	};
}