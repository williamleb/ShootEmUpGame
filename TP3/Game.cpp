#include "Game.h"
#include "RessourceManager.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "EndScene.h"

using namespace TP3;

/// <summary>
/// Crée une nouvelle <see cref="Game"/>.
/// </summary>
Game::Game()
{
	srand(time(NULL));
	mainWin.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Xador");
	mainWin.setVerticalSyncEnabled(true);
	//mainWin.setFramerateLimit(60);
	mainWin.setPosition(sf::Vector2i(mainWin.getPosition().x, 0));
}

/// <summary>
/// Fait jouer la partie.
/// </summary>
/// <returns>La sortie du programme.</returns>
int Game::run()
{
	RessourceManager::getInstance();

	Scene::scenes selecteurDeScene = Scene::scenes::TITLE;
	Scene::scenes sceneEnRetour;
	Scene* sceneActive = nullptr;

	unsigned int score = 0;
	bool won = false;

	while (true)
	{
		// Condition de sortie: la scène suivante est celle de sortie.
		if (selecteurDeScene == Scene::scenes::EXIT)
		{
			RessourceManager::deleteInstance();
			mainWin.close();
			return EXIT_SUCCESS;
		}
		else
		{
			// Sélectionne la classe concrète de la scène choisie.
			switch (selecteurDeScene)
			{
			case Scene::GAME:
				sceneActive = new GameScene();
				break;
			case Scene::TITLE:
				sceneActive = new TitleScene();
				break;
			case Scene::END:
				sceneActive = new EndScene();
				break;
			}

			if (EndScene* scene = dynamic_cast<EndScene*>(sceneActive))
			{
				scene->setInfo(score, won);
			}

			// On initialise la scène et on la fait jouer.
			if (sceneActive->init(&mainWin))
			{
				sceneEnRetour = sceneActive->run();
			}
			else
			{
				// Condition de sortie: la scène ne s'est pas initialisée correctement.
				RessourceManager::getInstance()->clear();
				RessourceManager::deleteInstance();
				return EXIT_FAILURE;
			}
		}

		if (GameScene* scene = dynamic_cast<GameScene*>(sceneActive))
		{
			score = scene->getScore();
			won = scene->isCompleted();
		}

		selecteurDeScene = sceneEnRetour;
		delete sceneActive;
		sceneActive = nullptr;
	}
}
