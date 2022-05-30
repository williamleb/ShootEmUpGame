#include "Activatable.h"

using namespace TP3;

/// <summary>
/// Cr�e un nouveau <see cref="Activatable"/>.
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
/// Active l'objet � une position sp�cifique.
/// </summary>
/// <param name="position">La position � laquelle activer le joueur.</param>
void Activatable::activate(const sf::Vector2f& position)
{
	activated = true;
}

/// <summary>
/// D�sactive l'objet.
/// </summary>
void Activatable::deactivate()
{
	activated = false;
}

/// <summary>
/// D�termine si l'objet est activ�.
/// </summary>
/// <returns>true si l'objet est activ�; false sinon.</returns>
bool Activatable::isActivated() const
{
	return activated;
}