#include "EndScene.h"
#include <sstream>

using namespace TP3;

EndScene::EndScene()
	: won(false), score(0)
{
	ressourceManager = RessourceManager::getInstance();
}

/// <summary>
/// Change les informations de partie.
/// </summary>
/// <param name="score">Le score final du joueur.</param>
/// <param name="won">true si le joueur a gagné; false sinon.</param>
void EndScene::setInfo(const unsigned int score, const bool won)
{
	this->score = score;	
	this->won = won;
}

EndScene::~EndScene()
{
	ressourceManager->clear();

	for (unsigned int i = 0; i < NBR_BACKGROUNDS; i++)
	{
		delete allBackgrounds[i];
	}
}

Scene::scenes EndScene::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool EndScene::init(RenderWindow * const window)
{

	if (!ressourceManager->addTexture("Ressources\\Sprites\\Background\\Layer1.png", TEXTURE_BACKGROUND_LAYER1))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Background\\Layer2.png", TEXTURE_BACKGROUND_LAYER2))
	{
		return false;
	}
	if (!ressourceManager->addTexture("Ressources\\Sprites\\Background\\Layer3.png", TEXTURE_BACKGROUND_LAYER3))
	{
		return false;
	}

	if (!ressourceManager->addTexture("Ressources\\Sprites\\HUD\\score.png", TEXTURE_SCORE))
	{
		return false;
	}

	if (!font.loadFromFile("Ressources\\Fonts\\Inky Thin Pixels.ttf"))
	{
		return false;
	}
	if (!ressourceManager->addMusic("Ressources\\Sounds\\missionFailed.wav", SOUND_END))
	{
		return false;
	}
	sf::Music *music = ressourceManager->getMusic(SOUND_END);
	music->setVolume(25);
	if (!won)
	{
		music->play();
	}

	ressourceManager->addSprite(TEXTURE_BACKGROUND_LAYER1, SPRITE_BACKGROUND_LAYER1);
	ressourceManager->addSprite(TEXTURE_BACKGROUND_LAYER2, SPRITE_BACKGROUND_LAYER2);
	ressourceManager->addSprite(TEXTURE_BACKGROUND_LAYER3, SPRITE_BACKGROUND_LAYER3);
	ressourceManager->addSprite(TEXTURE_SCORE, SPRITE_SCORE);

	allBackgrounds[0] = new Background(3, 1, SPRITE_BACKGROUND_LAYER3);
	allBackgrounds[1] = new Background(3, 2, SPRITE_BACKGROUND_LAYER3);
	allBackgrounds[2] = new Background(2, 1, SPRITE_BACKGROUND_LAYER2);
	allBackgrounds[3] = new Background(2, 2, SPRITE_BACKGROUND_LAYER2);
	allBackgrounds[4] = new Background(1, 1, SPRITE_BACKGROUND_LAYER1);
	allBackgrounds[5] = new Background(1, 2, SPRITE_BACKGROUND_LAYER1);

	// Initialise les textes.
	Text* text = nullptr;

	ressourceManager->addText("", TEXT_MISSION);
	text = ressourceManager->getText(TEXT_MISSION);
	text->setFont(font);
	text->setFillColor(Color::White);
	text->setOutlineColor(Color::Black);
	text->setOutlineThickness(2);
	text->setCharacterSize(150);
	if (won)
	{
		text->setPosition(175, 450);
		text->setString("Mission Complete");
	}
	else
	{
		text->setPosition(300, 450);
		text->setString("Mission Failed");
	}


	ressourceManager->addText("Appuyez sur Espace pour rejouer", TEXT_RESTART);
	text = ressourceManager->getText(TEXT_RESTART);
	text->setFont(font);
	text->setFillColor(Color::White);
	text->setCharacterSize(40);
	text->setOutlineColor(Color::Black);
	text->setOutlineThickness(1);
	text->setPosition(400, 750);

	ressourceManager->addText("Appuyez sur Escape pour revenir à l'écran titre", TEXT_RETURN);
	text = ressourceManager->getText(TEXT_RETURN);
	text->setFont(font);
	text->setFillColor(Color::White);
	text->setCharacterSize(40);
	text->setOutlineColor(Color::Black);
	text->setOutlineThickness(1);
	text->setPosition(300, 800);

	ressourceManager->addText("", TEXT_SCORE);
	text = ressourceManager->getText(TEXT_SCORE);
	text->setFont(font);
	text->setFillColor(Color::White);
	text->setCharacterSize(90);
	text->setOutlineColor(Color::Black);
	text->setOutlineThickness(1);
	text->setPosition(675, 120);
	std::stringstream scoreStreamStream;
	scoreStreamStream << score;
	std::string scoreString = scoreStreamStream.str();
	while (scoreString.length() != NBR_CHARACTERS_IN_SCORE)
	{
		scoreString.insert(0, "0");
	}
	text->setString(scoreString);

	this->mainWin = window;
	isRunning = true;

	return true;
}

void EndScene::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			isRunning = false;
			transitionVersScene = Scene::scenes::EXIT;
		}
		//manette
		if (sf::Joystick::isConnected(0))
		{
			//b
			if (sf::Joystick::isButtonPressed(0, 1))
			{
				isRunning = false;
				transitionVersScene = scenes::GAME;
			}
			//x
			if (sf::Joystick::isButtonPressed(0, 2))
			{
				isRunning = false;
				transitionVersScene = scenes::TITLE;
			}

		}
		//Un événement de touche de clavier
		if (event.type == Event::KeyPressed)
		{
			// Escape
			if (event.key.code == Keyboard::Escape)
			{
				isRunning = false;
				transitionVersScene = scenes::TITLE;
			}
			// Espace
			else if (event.key.code == Keyboard::Space)
			{
				isRunning = false;
				transitionVersScene = scenes::GAME;
			}
		}
	}
}

void EndScene::update()
{
	float deltaT = 1.0f / 60.0f;
	for (unsigned int i = 0; i < NBR_BACKGROUNDS; i++)
	{
		allBackgrounds[i]->update(deltaT);
	}
}

void EndScene::draw()
{
	mainWin->clear();
	for (unsigned int i = 0; i < NBR_BACKGROUNDS; i++)
	{
		allBackgrounds[i]->draw(*mainWin);
	}

	mainWin->draw(*RessourceManager::getInstance()->getSprite(SPRITE_SCORE));

	mainWin->draw(*RessourceManager::getInstance()->getText(TEXT_SCORE));
	mainWin->draw(*RessourceManager::getInstance()->getText(TEXT_RESTART));
	mainWin->draw(*RessourceManager::getInstance()->getText(TEXT_RETURN));
	mainWin->draw(*RessourceManager::getInstance()->getText(TEXT_MISSION));

	mainWin->display();
}