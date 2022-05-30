#include "TitleScene.h"

using namespace TP3;

TitleScene::TitleScene()
	: flashTimer(sf::microseconds(0))
{
	ressourceManager = RessourceManager::getInstance();
}

TitleScene::~TitleScene()
{
	ressourceManager->clear();

	for (unsigned int i = 0; i < NBR_BACKGROUNDS; i++)
	{
		delete allBackgrounds[i];
	}
}

Scene::scenes TitleScene::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool TitleScene::init(RenderWindow * const window)
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

	if (!ressourceManager->addTexture("Ressources\\Sprites\\HUD\\instructions.png", TEXTURE_INSTRUCTIONS))
	{
		return false;
	}

	if (!font.loadFromFile("Ressources\\Fonts\\Inky Thin Pixels.ttf"))
	{
		return false;
	}
	if (!ressourceManager->addMusic("Ressources\\Sounds\\mainMenu.wav", SOUND_MAIN_MENU))
	{
		return false;
	}
	sf::Music *music = ressourceManager->getMusic(SOUND_MAIN_MENU);
	music->setVolume(25);
	music->play();

	ressourceManager->addSprite(TEXTURE_BACKGROUND_LAYER1, SPRITE_BACKGROUND_LAYER1);
	ressourceManager->addSprite(TEXTURE_BACKGROUND_LAYER2, SPRITE_BACKGROUND_LAYER2);
	ressourceManager->addSprite(TEXTURE_BACKGROUND_LAYER3, SPRITE_BACKGROUND_LAYER3);
	ressourceManager->addSprite(TEXTURE_INSTRUCTIONS, SPRITE_INSTRUCTIONS);

	allBackgrounds[0] = new Background(3, 1, SPRITE_BACKGROUND_LAYER3);
	allBackgrounds[1] = new Background(3, 2, SPRITE_BACKGROUND_LAYER3);
	allBackgrounds[2] = new Background(2, 1, SPRITE_BACKGROUND_LAYER2);
	allBackgrounds[3] = new Background(2, 2, SPRITE_BACKGROUND_LAYER2);
	allBackgrounds[4] = new Background(1, 1, SPRITE_BACKGROUND_LAYER1);
	allBackgrounds[5] = new Background(1, 2, SPRITE_BACKGROUND_LAYER1);

	// Initialise les textes.
	Text* text = nullptr;

	ressourceManager->addText("XADOR", TEXT_TITLE);
	text = ressourceManager->getText(TEXT_TITLE);
	text->setFont(font);
	text->setFillColor(Color::White);
	text->setOutlineColor(Color::Black);
	text->setOutlineThickness(2);
	text->setCharacterSize(200);
	text->setPosition(450, 450);

	ressourceManager->addText("Appuyez sur Espace pour jouer", TEXT_BEGIN);
	text = ressourceManager->getText(TEXT_BEGIN);
	text->setFont(font);
	text->setFillColor(Color::White);
	text->setCharacterSize(40);
	text->setOutlineColor(Color::Black);
	text->setOutlineThickness(1);
	text->setPosition(425, 750);

	this->mainWin = window;
	isRunning = true;
	flashTimer = sf::microseconds(0);


	return true;
}

void TitleScene::getInputs()
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
		}

		//Un événement de touche de clavier
		if (event.type == Event::KeyPressed)
		{
			// Escape
			if (event.key.code == Keyboard::Escape)
			{
				isRunning = false;
				transitionVersScene = scenes::EXIT;
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

void TitleScene::update()
{
	float deltaT = 1.0f / 60.0f;
	flashTimer += sf::seconds(deltaT);
	for (unsigned int i = 0; i < NBR_BACKGROUNDS; i++)
	{
		allBackgrounds[i]->update(deltaT);
	}
}

void TitleScene::draw()
{
	mainWin->clear();
	for (unsigned int i = 0; i < NBR_BACKGROUNDS; i++)
	{
		allBackgrounds[i]->draw(*mainWin);
	}

	mainWin->draw(*RessourceManager::getInstance()->getSprite(SPRITE_INSTRUCTIONS));

	mainWin->draw(*RessourceManager::getInstance()->getText(TEXT_TITLE));

	if (flashTimer.asMilliseconds() % NBR_MILLISECONDS_FOR_FLASH <= NBR_MILLISECONDS_FOR_FLASH * 0.5f)
	{
		mainWin->draw(*RessourceManager::getInstance()->getText(TEXT_BEGIN));
	}
	mainWin->display();
}