#include "Shield.h"

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="Shield"/> avec un nombre de points de vie entre 1 et 3.
/// </summary>
/// <param name="color">La couleur du bouclier.</param>
Shield::Shield(const sf::Color& color)
	:color(color)
{
	// Donne un nombre de vie au bouclier au hasard (de 1 à 3 pts de vie).
	resetLife((rand() % 3) + 1);
}

/// <summary>
/// Retourne la couleur du bouclier.
/// </summary>
/// <returns>La couleur du bouclier.</returns>
const sf::Color& Shield::getColor() const
{
	return color;
}

/// <summary>
/// Fait subit des dégats au bouclier sauf si la couleur de ce
/// qui le touche est la même que la couleur du bouclier.
/// </summary>
/// <param name="life">Le dommage subit.</param>
/// <param name="dammageColor">La couleur de ce qui fait perdre du dommage au bouclier.</param>
void Shield::damage(const unsigned int life, const sf::Color& dammageColor)
{
	// Le bouclier subit seulement des dommages si ce qui l'endommage n'est pas de
	// la même couleur que lui.
	if (dammageColor != color)
	{
		Destroyable::damage(life);

		// On notifie les observateur du shield quand celui-ci se brise.
		if (isDestroyed())
		{
			notifierTousLesObservateurs();
		}
	}
}