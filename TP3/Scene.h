#pragma once

#include <SFML/Graphics.hpp>
#include "RessourceManager.h"

using namespace sf;


namespace TP3
{
	class Controller;

	/// <summary>
	/// Repr�sente une sc�ne (une vue) dans le jeu.
	/// </summary>
	class Scene
	{
	public:
		// Toutes les sc�nes du jeu.
		enum scenes { EXIT, GAME, TITLE, END };

		virtual ~Scene() {}
		
		/// <summary>
		/// Joue la sc�ne.
		/// </summary>
		/// <returns>La prochaine sc�ne � jouer.</returns>
		virtual scenes run() = 0;
		

		/// <summary>
		/// Initialise la sc�ne.
		/// Doit �tre appel� une fois avant de jouer la sc�ne.
		/// </summary>
		/// <param name="window">La fen�tre sur laquelle s'affichera la sc�ne.</param>
		/// <returns>True si l'initialisation s'est effectu�e correctement; false sinon.</returns>
		virtual bool init(RenderWindow * const window) = 0;		

		/// <summary>
		/// G�re toutes les commandes entr�es dans la sc�ne.
		/// </summary>
		virtual void getInputs() = 0;
		
		/// <summary>
		/// Met � jour la sc�ne.
		/// </summary>
		virtual void update() = 0;
		
		/// <summary>
		/// Affiche la sc�ne.
		/// </summary>
		virtual void draw() = 0;

	protected:
		RenderWindow *mainWin;

		Event event;
		
		/// <summary>
		/// � la fin de chaque sc�ne, on indique � Game quelle nouvelle sc�ne elle doit charger.
		/// </summary>
		Scene::scenes transitionVersScene;
		bool isRunning;

		RessourceManager* ressourceManager;
		Controller* controller;
	};
}