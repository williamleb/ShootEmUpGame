#include "FollowedCommands.h"
#include "FollowEntity.h"

using namespace TP3;

/// <summary>
/// Crée une nouvelle <see cref="FollowedCommand_Base"/>.
/// </summary>
/// <param name="whenHappened">Le temps où la commande a été faite.</param>
FollowedCommand_Base::FollowedCommand_Base(const sf::Time& whenHappened)
	:whenHappened(whenHappened)
{
}

/// <summary>
/// Crée une nouvelle <see cref="FollowedCommand_ChangeDirection"/>.
/// </summary>
/// <param name="direction">La direction de la commande.</param>
/// <param name="whenHappened">Le temps où la commande a été faite.</param>
FollowedCommand_ChangeDirection::FollowedCommand_ChangeDirection(const sf::Vector2f& direction, const sf::Time& whenHappened)
	:direction(direction), FollowedCommand_Base(whenHappened)
{
}

/// <summary>
/// Exécute la commande: change la direction de l'ennemi.
/// </summary>
/// <param name="entity">L'ennemi avec lequel changer la direction.</param>
void FollowedCommand_ChangeDirection::execute(FollowEntity* entity) const
{
	entity->changeDirection(direction);
}

/// <summary>
/// Retourne la direction de la commande.
/// </summary>
/// <returns>La direction de la commande.</returns>
const sf::Vector2f FollowedCommand_ChangeDirection::getDirection() const
{
	return direction;
}

/// <summary>
/// Crée une nouvelle <see cref="FollowedCommand_Fire"/>.
/// </summary>
/// <param name="whenHappened">Le temps où la commande a été faite.</param>
FollowedCommand_Fire::FollowedCommand_Fire(const sf::Time& whenHappened)
	:FollowedCommand_Base(whenHappened)
{
}

/// <summary>
/// Exécute la commande: fait tirer l'ennemi.
/// </summary>
/// <param name="entity">L'ennemi avec lequel tirer.</param>
void FollowedCommand_Fire::execute(FollowEntity* entity) const
{
	entity->fireCommand();
}