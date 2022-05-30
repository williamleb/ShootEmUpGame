#include "PlayerCommands.h"
#include "UserControlled.h"

using namespace TP3;

/// <summary>
/// Crée une nouvelle <see cref="PlayerCommand_Base"/>.
/// </summary>
/// <param name="whenHappened">Le temps où la commande a été faite.</param>
PlayerCommand_Base::PlayerCommand_Base(const sf::Time& whenHappened)
	:whenHappened(whenHappened)
{
}

/// <summary>
/// Crée une nouvelle <see cref="PlayerCommand_ChangeDirection"/>.
/// </summary>
/// <param name="direction">La direction de la commande.</param>
/// <param name="whenHappened">Le temps où la commande a été faite.</param>
PlayerCommand_ChangeDirection::PlayerCommand_ChangeDirection(const sf::Vector2f& direction, const sf::Time& whenHappened)
	:direction(direction), PlayerCommand_Base(whenHappened)
{
}

/// <summary>
/// Exécute la commande: change la direction du joueur.
/// </summary>
/// <param name="player">Le joueur avec lequel changer la direction.</param>
void PlayerCommand_ChangeDirection::execute(UserControlled* player) const
{
	player->changeDirection(direction);
}

/// <summary>
/// Retourne la direction de la commande.
/// </summary>
/// <returns>La direction de la commande.</returns>
const sf::Vector2f PlayerCommand_ChangeDirection::getDirection() const
{
	return direction;
}

/// <summary>
/// Crée une nouvelle <see cref="PlayerCommand_Fire"/>.
/// </summary>
/// <param name="whenHappened">Le temps où la commande a été faite.</param>
PlayerCommand_Fire::PlayerCommand_Fire(const sf::Time& whenHappened)
	:PlayerCommand_Base(whenHappened)
{
}

/// <summary>
/// Exécute la commande: fait tirer le joueur.
/// </summary>
/// <param name="player">Le joueur avec lequel tirer.</param>
void PlayerCommand_Fire::execute(UserControlled* player) const
{
	player->fire();
}