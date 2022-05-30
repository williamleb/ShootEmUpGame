#include "Followed.h"
#include "GameScene.h"

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="Followed"/>.
/// </summary>
Followed::Followed()
	: Trooper(FOLLOWED)
{
}

/// <summary>
/// Détruit le <see cref="Followed"/>.
/// </summary>
Followed::~Followed()
{
	while (!inputs.getCommands().empty())
	{
		inputs.removeCommand();
	}
}

/// <summary>
/// Met à jour le Followed.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel d'update.</param>
void Followed::update(const float deltaT)
{
	if (isActivated())
	{
		sf::Vector2f oldDir = getDirection();
		Trooper::update(deltaT);

		// Si le Followed a une nouvelle direction, on ajoute celle-ci aux commandes.
		if (oldDir != getDirection())
		{
			sf::Time whenHappened = getGameScene()->getTimeSinceStart();
			inputs.storeAndExecute(new FollowedCommand_ChangeDirection(getDirection(), whenHappened), this);
		}

		// S'il y a des commandes...
		if (!inputs.getCommands().empty())
		{
			// Si ça fait assez longtemps que la commande est stockée...
			if ((getGameScene()->getTimeSinceStart().asMilliseconds() - inputs.getCommands().front()->whenHappened.asMilliseconds()) > MS_BEFORE_COMMAND_REMOVAL)
			{
				// On l'enlève.
				inputs.removeCommand();
			}
		}
	}
}

/// <summary>
/// Fait tirer le Followed.
/// </summary>
void Followed::fire()
{
	// Le Followed ne tire pas, mais il place le tir en commande pour que ses Follower puissent tirer.
	sf::Time whenHappened = getGameScene()->getTimeSinceStart();
	inputs.storeCommand(new FollowedCommand_Fire(whenHappened));
}

/// <summary>
/// Remet le Followed à un état de départ.
/// </summary>
void Followed::reset()
{
	while (!inputs.getCommands().empty())
	{
		inputs.removeCommand();
	}

	Trooper::reset();
}

/// <summary>
/// Endommage le Followed.
/// </summary>
/// <param name="life">Les dégâts à faire au Followed.</param>
void Followed::damage(const unsigned int life)
{
	// L'ennemi Followed ne se prend pas de dommages.
}

/// <summary>
/// Endommage le Followed.
/// </summary>
/// <param name="life">Les dégâts à faire au Followed.</param>
/// <param name="dammageColor">La couleur des dommages à faire.</param>
void Followed::damage(const unsigned int life, const sf::Color& dammageColor)
{
	// L'ennemi Followed ne se prend pas de dommages.
}

/// <summary>
/// Active le Followed.
/// </summary>
void Followed::activate()
{
	Trooper::activate();

	// Le Followed active plusieurs Follower.
	for (int i = 0; i < NBR_MAX_FOLLOWER; ++i)
	{
		getGameScene()->activateFollower(this);
	}
}

/// <summary>
/// Active le Followed.
/// </summary>
/// <param name="position">La position à activer le Followed.</param>
void Followed::activate(const sf::Vector2f& position)
{
	Trooper::activate(position);

	// Le Followed active plusieurs Follower.
	for (int i = 0; i < NBR_MAX_FOLLOWER; ++i)
	{
		getGameScene()->activateFollower(this);
	}
}

/// <summary>
/// Désactive le Followed.
/// </summary>
void Followed::deactivate()
{
	// Désactive le Followed seulement s'il n'a plus de Follower.
	if (allCurrentFollowers.empty())
	{
		Trooper::deactivate();
	}
}

/// <summary>
/// Affiche le Followed.
/// </summary>
/// <param name="window">La fenêtre sur laquelle afficher le Followed.</param>
void Followed::draw(sf::RenderWindow& window)
{
	// L'ennemi Followed ne s'affiche pas.
}

/// <summary>
/// Ajoute un Follower au Followed.
/// </summary>
/// <param name="follower">Le Follower à ajouter.</param>
/// <returns>La position du Follower dans la liste.</returns>
unsigned int Followed::addFollower(Follower* follower)
{
	//if (std::find(allCurrentFollowers.begin(), allCurrentFollowers.end(), follower) != allCurrentFollowers.end())
	//{
		allCurrentFollowers.push_back(follower);
	//}

	return allCurrentFollowers.size();
}

/// <summary>
/// Retire un Follower de la liste du Followed.
/// </summary>
/// <param name="follower">Le Follower à enlever.</param>
void Followed::removeFollower(Follower* follower)
{
	//if (std::find(allCurrentFollowers.begin(), allCurrentFollowers.end(), follower) != allCurrentFollowers.end())
	//{
		allCurrentFollowers.remove(follower);
	//}
}

/// <summary>
/// Commande de changement de direction.
/// </summary>
/// <param name="direction">La nouvelle direction du Followed.</param>
void Followed::changeDirection(const sf::Vector2f direction)
{
	setDirection(direction);
}

/// <summary>
/// Commande de tir.
/// </summary>
void Followed::fireCommand()
{
	// Le Followed ne tire pas.
}

/// <summary>
/// Retourne les inputs du Followed.
/// </summary>
/// <returns>Les inputs du Followed.</returns>
FollowedInputs& Followed::getInputs()
{
	return inputs;
}