#include "Option.h"
#include "GameScene.h"

using namespace TP3;

/// <summary>
/// Crée une nouvelle <see cref="Option"/>.
/// </summary>
Option::Option()
	:UserControlled(GameObject::ObjectType::OPTION), timeSinceSpawnedInMs(0), timerAnimation(sf::microseconds(0)),
	fireTimer(sf::microseconds(0)), lastTimeShoot(sf::microseconds(0))
{
}

/// <summary>
/// Initialise l'option.
/// Cette méthode doit être appelée une fois avant d'utiliser l'option.
/// </summary>
/// <param name="spriteKey">La clé du psrite utilisé par l'option.</param>
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
/// <param name="position">La position à laquelle l'option est activée.</param>
void Option::activate(const sf::Vector2f& position)
{
	addUserControlled(this);
	setPosition(position);
	timeSinceSpawnedInMs = 0;
	
	// Le timer intérieur des options commence au temps actuel - le décalage
	// Le décalage correspond à la valeur de décalage par défaut * le numéro de l'option.
	innerTimer = sf::milliseconds(getGameScene()->getTimeSinceStart().asMilliseconds() - (MS_MOVING_DELAY * getPositionAmongUserControlled()));
	timeStartedInMs = getGameScene()->getTimeSinceStart().asMilliseconds();
	lastTimeShoot = getGameScene()->getTimeSinceStart();

	// Pour que l'option démarre dans la direction du joueur, il faut qu'il y ait une commande qui débute
	// lorsque l'option est activée.
	player->getPlayerInputs().storeCommand(new PlayerCommand_ChangeDirection(player->getDirection(), getGameScene()->getTimeSinceStart() + sf::microseconds(1)));

	fireTimer = sf::microseconds(0);

	Activatable::activate();
}

/// <summary>
/// Désactive l'option.
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
/// Met à jour l'option.
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

		// Si on a dépassé le délais d'attente pour que l'option commencer à bouger...
		if (innerTimer.asMilliseconds() >= timeStartedInMs)
		{
			// S'il y a des commandes dans la liste...
			if (!commands.empty())
			{
				// On cherche la commande à exécuter selon le décalage...
				int currentCommand = 0;
				while (currentCommand < commands.size() && innerTimer > commands[currentCommand]->whenHappened)
				{
					currentCommand++;
				}
				currentCommand--;

				// Si on a trouvé une commande à effectué selon le décalage...
				if (currentCommand != -1)
				{
					// Si la commande n'en est pas une de tir...
					if (PlayerCommand_ChangeDirection* command = dynamic_cast<PlayerCommand_ChangeDirection*>(commands[currentCommand]))
					{
						// L'option exécute la commande.
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

		// Si l'option est la dernière, elle peut gérer les commandes et sa désactivation.
		if (isLast())
		{
			// S'il y a des commandes...
			if (!commands.empty())
			{
				// Si ça fait assez longtemps que la commande est stockée...
				if ((getGameScene()->getTimeSinceStart().asMilliseconds() - commands.front()->whenHappened.asMilliseconds()) > MS_BEFORE_COMMAND_REMOVAL * (getPositionAmongUserControlled() + 1))
				{
					// On l'enlève.
					player->getPlayerInputs().removeCommand();
				}
			}

			// Si ça fait assez longtemps que l'option est en vie...
			if (timeSinceSpawnedInMs > MS_LIFETIME)
			{
				// Elle se désactive.
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
/// Affiche l'option sur la fenêtre.
/// </summary>
/// <param name="window">La fenêtre sur laquelle afficher l'option.</param>
void Option::draw(sf::RenderWindow& window)
{
	if (isActivated())
	{
		RessourceManager::getInstance()->getSprite(getSpriteKey())->setTextureRect(*currentRect);
		UserControlled::draw(window);
	}
}

/// <summary>
/// Ajuste l'option à l'intérieur des limites du jeu.
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