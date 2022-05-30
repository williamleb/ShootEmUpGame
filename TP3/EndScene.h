#pragma once

#include "Scene.h"
#include <vector>
#include "Background.h"

namespace TP3
{
	/// <summary>
	/// Scène de fin de partie.
	/// </summary>
	/// <seealso cref="Scene" />
	class EndScene : public Scene
	{

		enum Ressource : RessourceManager::key
		{
			TEXTURE_BACKGROUND_LAYER1 = 001,
			TEXTURE_BACKGROUND_LAYER2,
			TEXTURE_BACKGROUND_LAYER3,
			TEXTURE_SCORE,

			SPRITE_BACKGROUND_LAYER1 = 101,
			SPRITE_BACKGROUND_LAYER2,
			SPRITE_BACKGROUND_LAYER3,
			SPRITE_SCORE,

			TEXT_MISSION = 201,
			TEXT_RESTART,
			TEXT_RETURN,
			TEXT_SCORE,

			SOUND_END=301,
		};

		// L'interface de la scène
		Font font;

		const static int NBR_BACKGROUNDS = 6;
		Background* allBackgrounds[NBR_BACKGROUNDS];

		static const int NBR_CHARACTERS_IN_SCORE = 12;
		unsigned int score;
		bool won;

	public:
		EndScene();
		~EndScene();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();

		void setInfo(const unsigned int score, const bool won);
	};
}