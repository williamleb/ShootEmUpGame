#include "Activatable.h"

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="Activatable"/>.
/// </summary>
Activatable::Activatable()
	:activated(false)
{
}

/// <summary>
/// Active l'objet.
/// </summary>
void Activatable::activate()
{
	activated = true;
}

/// <summary>
/// Active l'objet à une position spécifique.
/// </summary>
/// <param name="position">La position à laquelle activer le joueur.</param>
void Activatable::activate(const sf::Vector2f& position)
{
	activated = true;
}

/// <summary>
/// Désactive l'objet.
/// </summary>
void Activatable::deactivate()
{
	activated = false;
}

/// <summary>
/// Détermine si l'objet est activé.
/// </summary>
/// <returns>true si l'objet est activé; false sinon.</returns>
bool Activatable::isActivated() const
{
	return activated;
}