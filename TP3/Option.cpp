#include "Option.h"
#include "GameScene.h"

using namespace TP3;

/// <summary>
/// Cr�e une nouvelle <see cref="Option"/>.
/// </summary>
Option::Option()
	:UserControlled(GameObject::ObjectType::OPTION), timeSinceSpawnedInMs(0), timerAnimation(sf::microseconds(0)),
	fireTimer(sf::microseconds(0)), lastTimeShoot(sf::microseconds(0))
{
}

/// <summary>
/// Initialise l'option.
/// Cette m�thode doit �tre appel�e une fois avant d'utiliser l'option.
/// </summary>
/// <param name="spriteKey">La cl� du psrite utilis� par l'option.</param>
/// <param name="player">Le joueur qui l'option suit..</param>
/// <returns></returns>
bool Option::init(const RessourceManager::key spriteKey, TP3::Player* player)
{
	setSpeed(Player::PLAYER_DEFAULT_SPEED);

	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(OPTION_WIDTH / 2, OPTION_HEIGHT / 2);

	for (unsigned int i = 0; i < NBR_ANIM; i++)
	{
		animation[i] = sf::IntRect(i * OPTION_WIDTH, 0, OPTION_WIDTH, OPTION_HEIGHT);
	}
	currentRect = &animation[0];
	timerAnimation = sf::milliseconds(0);
	sprite->setTextureRect(*currentRect);

	setDimension(OPTION_WIDTH, OPTION_HEIGHT);
	this->player = player;

	return true;
}

/// <summary>
/// Active l'option.
/// </summary>
/// <param name="position">La position � laquelle l'option est activ�e.</param>
void Option::activate(const sf::Vector2f& position)
{
	addUserControlled(this);
	setPosition(position);
	timeSinceSpawnedInMs = 0;
	
	// Le timer int�rieur des options commence au temps actuel - le d�calage
	// Le d�calage correspond � la valeur de d�calage par d�faut * le num�ro de l'option.
	innerTimer = sf::milliseconds(getGameScene()->getTimeSinceStart().asMilliseconds() - (MS_MOVING_DELAY * getPositionAmongUserControlled()));
	timeStartedInMs = getGameScene()->getTimeSinceStart().asMilliseconds();
	lastTimeShoot = getGameScene()->getTimeSinceStart();

	// Pour que l'option d�marre dans la direction du joueur, il faut qu'il y ait une commande qui d�bute
	// lorsque l'option est activ�e.
	player->getPlayerInputs().storeCommand(new PlayerCommand_ChangeDirection(player->getDirection(), getGameScene()->getTimeSinceStart() + sf::microseconds(1)));

	fireTimer = sf::microseconds(0);

	Activatable::activate();
}

/// <summary>
/// D�sactive l'option.
/// </summary>
void Option::deactivate()
{
	if (isLast())
	{
		removeLastUserControlled();

		Activatable::deactivate();
	}
}

/// <summary>
/// Met � jour l'option.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel d'update.</param>
void Option::update(const float deltaT)
{
	if (isActivated())
	{
		fireTimer += sf::seconds(deltaT);

		const TP3_structures::deque<PlayerCommand_Base*>& commands = player->getPlayerInputs().getCommands();

		timeSinceSpawnedInMs += deltaT * 1000;

		innerTimer += sf::seconds(deltaT);

		// Si on a d�pass� le d�lais d'attente pour que l'option commencer � bouger...
		if (innerTimer.asMilliseconds() >= timeStartedInMs)
		{
			// S'il y a des commandes dans la liste...
			if (!commands.empty())
			{
				// On cherche la commande � ex�cuter selon le d�calage...
				int currentCommand = 0;
				while (currentCommand < commands.size() && innerTimer > commands[currentCommand]->whenHappened)
				{
					currentCommand++;
				}
				currentCommand--;

				// Si on a trouv� une commande � effectu� selon le d�calage...
				if (currentCommand != -1)
				{
					// Si la commande n'en est pas une de tir...
					if (PlayerCommand_ChangeDirection* command = dynamic_cast<PlayerCommand_ChangeDirection*>(commands[currentCommand]))
					{
						// L'option ex�cute la commande.
						command->execute(this);
					}
				}
			}
			UserControlled::update(deltaT);
		}
		else
		{
			sf::Vector2f oldDir = getDirection();
			setDirection(IDLE);
			UserControlled::update(deltaT);
			setDirection(oldDir);
		}

		fire();

		adjustIntoMap();

		// Si l'option est la derni�re, elle peut g�rer les commandes et sa d�sactivation.
		if (isLast())
		{
			// S'il y a des commandes...
			if (!commands.empty())
			{
				// Si �a fait assez longtemps que la commande est stock�e...
				if ((getGameScene()->getTimeSinceStart().asMilliseconds() - commands.front()->whenHappened.asMilliseconds()) > MS_BEFORE_COMMAND_REMOVAL * (getPositionAmongUserControlled() + 1))
				{
					// On l'enl�ve.
					player->getPlayerInputs().removeCommand();
				}
			}

			// Si �a fait assez longtemps que l'option est en vie...
			if (timeSinceSpawnedInMs > MS_LIFETIME)
			{
				// Elle se d�sactive.
				deactivate();
			}
		}

		animate(deltaT);
	}
}

/// <summary>
/// Commande qui change la direction de l'option.
/// </summary>
/// <param name="direction">La direction de loption..</param>
void Option::changeDirection(const sf::Vector2f direction)
{
	setDirection(direction);
}

/// <summary>
/// Commande qui fait tirer l'option.
/// </summary>
void Option::fire()
{
	if (fireTimer.asMilliseconds() >= MS_FIRERATE)
	{
 		getGameScene()->activateMovable(GameObject::ObjectType::BEAM, getPosition(), Direction::RIGHT);
		fireTimer = sf::microseconds(0);
	}
}

/// <summary>
/// Affiche l'option sur la fen�tre.
/// </summary>
/// <param name="window">La fen�tre sur laquelle afficher l'option.</param>
void Option::draw(sf::RenderWindow& window)
{
	if (isActivated())
	{
		RessourceManager::getInstance()->getSprite(getSpriteKey())->setTextureRect(*currentRect);
		UserControlled::draw(window);
	}
}

/// <summary>
/// Ajuste l'option � l'int�rieur des limites du jeu.
/// </summary>
void Option::adjustIntoMap()
{
	sf::Vector2f pos = getPosition();
	sf::Vector2f halfSize = player->getDimension() * 0.5f;
	GameScene* game = getGameScene();

	// Limites horizontales.
	if (pos.x - halfSize.x < game->GAME_LEFT)
	{
		setPosition(game->GAME_LEFT + halfSize.x, pos.y);
	}
	else if (pos.x + halfSize.x >= game->GAME_LEFT + game->GAME_WIDTH)
	{
		setPosition(game->GAME_LEFT + game->GAME_WIDTH - halfSize.x - 1, pos.y);
	}

	pos = getPosition();

	// Limites vertivales.
	if (pos.y - halfSize.y < game->GAME_TOP)
	{
		setPosition(pos.x, game->GAME_TOP + halfSize.y);
	}
	else if (pos.y + halfSize.y >= game->GAME_TOP + game->GAME_HEIGHT)
	{
		setPosition(pos.x, game->GAME_TOP + game->GAME_HEIGHT - halfSize.y - 1);
	}
}

/// <summary>
/// Anime l'option.
/// </summary>
void Option::animate(const float deltaT)
{
	timerAnimation += sf::seconds(deltaT);

	int currentRectAnim = timerAnimation.asMilliseconds() / MS_PER_FRAME;

	if (currentRectAnim >= NBR_ANIM)
	{
		currentRectAnim = 0;
		timerAnimation = sf::seconds(0);
	}

	currentRect = &animation[currentRectAnim];
}