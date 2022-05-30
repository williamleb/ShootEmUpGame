#include "Followed.h"
#include "GameScene.h"

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="Follower"/>.
/// </summary>
Follower::Follower()
	: Enemy(ObjectType::FOLLOWER, FOLLOWER_FIRERATE, FOLLOWER_DEFAULT_LIFE, FOLLOWER_DEFAULT_SPEED, FOLLOWER_POINTS, FOLLOWER_COLLISION_DAMAGE),
	followed(nullptr), timeSinceSpawnedInMs(0), lastTimeShoot(sf::microseconds(0))
{
}

/// <summary>
/// Update le Follower selon le temps écoulé.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la méthode.</param>
void Follower::update(const float deltaT)
{	
	if (isActivated())
	{
		const TP3_structures::deque<FollowedCommand_Base*>& commands = followed->getInputs().getCommands();

		timeSinceSpawnedInMs += deltaT * 1000;

		innerTimer += sf::seconds(deltaT);

		// Si on a dépassé le délais d'attente pour que le follower commencer à bouger...
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
					if (FollowedCommand_ChangeDirection* command = dynamic_cast<FollowedCommand_ChangeDirection*>(commands[currentCommand]))
					{
						// Le follower exécute la commande.
						command->execute(this);
					}
				}
			}
			Enemy::update(deltaT);
		}
		else
		{
			// Si ça fait pas assez longtemps, le follower reste immobile.
			sf::Vector2f oldDir = getDirection();
			setDirection(IDLE);
			Enemy::update(deltaT);
			setDirection(oldDir);
		}

		// S'il y a des commandes...
		if (!commands.empty())
		{
			// On cherche une nouvelle commande de tir (une qu'on n'a pas déjà exécutée).
			int currentCommand = 0;
			while (currentCommand < commands.size() && lastTimeShoot < commands[currentCommand]->whenHappened)
			{
				if (FollowedCommand_Fire* command = dynamic_cast<FollowedCommand_Fire*>(commands[currentCommand]))
				{
					// Si on en trouve une, on tir.
					command->execute(this);
					lastTimeShoot = command->whenHappened;
					break;
				}
				currentCommand++;
			}
		}


		// Le Follower ne peut pas sortir verticalement du jeu.
		if (getPosition().y - getDimension().y * 0.5f < GameScene::GAME_TOP)
		{
			setPosition(getPosition().x, GameScene::GAME_TOP + getDimension().y * 0.5f);
		}
		else if (getPosition().y + getDimension().y * 0.5f >= GameScene::GAME_TOP + GameScene::GAME_HEIGHT)
		{
			setPosition(getPosition().x, GameScene::GAME_TOP + GameScene::GAME_HEIGHT - 1 - getDimension().y * 0.5f);
		}
	}

}

/// <summary>
/// Initialise le Follower.
/// Doit être appelé une fois avant d'utiliser l'ennemi.
/// </summary>
/// <param name="spriteKey">Le sprite du Follower.</param>
/// <returns>true si l'initialisation s'est bien passée; false sinon.</returns>
bool Follower::init(const RessourceManager::key spriteKey)
{
	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(FOLLOWER_WIDTH / 2, FOLLOWER_HEIGHT / 2);
	setDimension(FOLLOWER_WIDTH, FOLLOWER_HEIGHT);

	return true;
}

/// <summary>
/// Fait tirer l'ennemi.
/// </summary>
void Follower::fire()
{
	// Le Follower ne tire pas normalement.
}

/// <summary>
/// Active le Follower pour un Followed.
/// </summary>
/// <param name="followed">Le Followed à suivre.</param>
void Follower::activate(Followed* followed)
{
	this->followed = followed;
	unsigned int pos = followed->addFollower(this);
	
	timeSinceSpawnedInMs = 0;

	// Le timer intérieur des options commence au temps actuel - le décalage
	// Le décalage correspond à la valeur de décalage par défaut * le numéro de l'option.
	innerTimer = sf::milliseconds(getGameScene()->getTimeSinceStart().asMilliseconds() - (MS_MOVING_DELAY * pos));
	timeStartedInMs = getGameScene()->getTimeSinceStart().asMilliseconds();

	// Pour que le Follower démarre dans la direction du Followed, il faut qu'il y ait une commande qui débute
	// lorsque le Follower est activée.
	followed->getInputs().storeCommand(new FollowedCommand_ChangeDirection(followed->getDirection(), getGameScene()->getTimeSinceStart() + sf::microseconds(1)));

	Enemy::activate(followed->getPosition());

	lastTimeShoot = sf::microseconds(0);
}

/// <summary>
/// Désactive l'ennemi.
/// </summary>
void Follower::deactivate()
{
	followed->removeFollower(this);

	Enemy::deactivate();
}

/// <summary>
/// Commande de tir.
/// </summary>
void Follower::fireCommand()
{
	GameScene* gameScene = getGameScene();
	gameScene->activateEnemyProjectile(ObjectType::LAZER, this, Direction::LEFT);
}

/// <summary>
/// Commande de changement de direction.
/// </summary>
/// <param name="direction">The direction.</param>
void Follower::changeDirection(const sf::Vector2f direction)
{
	setDirection(direction);
}

