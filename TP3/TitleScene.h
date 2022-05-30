#pragma once

#include "Scene.h"
#include <vector>
#include "Background.h"

namespace TP3
{	
	/// <summary>
	/// Sc�ne qui permet � l'utilisateur de naviguer � travers
	/// les diff�rentes sc�nes de gestion de compte.
	/// </summary>
	/// <seealso cref="Scene" />
	class TitleScene : public Scene
	{

		enum Ressource : RessourceManager::key
		{
			TEXTURE_BACKGROUND_LAYER1 = 001,
			TEXTURE_BACKGROUND_LAYER2,
			TEXTURE_BACKGROUND_LAYER3,
			TEXTURE_INSTRUCTIONS,

			SPRITE_BACKGROUND_LAYER1 = 101,
			SPRITE_BACKGROUND_LAYER2,
			SPRITE_BACKGROUND_LAYER3,
			SPRITE_INSTRUCTIONS,

			TEXT_TITLE = 201,
			TEXT_BEGIN,

			SOUND_MAIN_MENU=301,
		};

		// L'interface de la sc�ne
		Font font;

		const static int NBR_BACKGROUNDS = 6;
		Background* allBackgrounds[NBR_BACKGROUNDS];

		static const int NBR_MILLISECONDS_FOR_FLASH = 2000;
		sf::Time flashTimer;

	public:
		TitleScene();
		~TitleScene();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();
	};
}