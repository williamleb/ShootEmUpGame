#include "Destroyable.h"
#include <cmath>

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="Destroyable"/>.
/// </summary>
/// <param name="life">Les points de vie initiaux de l'objet.</param>
Destroyable::Destroyable(const unsigned int life, const unsigned int maxLife)
	:lifePts(life), maxLife(maxLife)
{
}

/// <summary>
/// Détermine si l'objet est détruit.
/// </summary>
/// <returns> <c>true</c> si l'objet est détruit; <c>false</c> sinon. </returns>
bool Destroyable::isDestroyed()
{
	return lifePts == 0;
}

/// <summary>
/// Retourne le nombre de vies restantes à l'objet.
/// </summary>
/// <returns>Le nombre de vies restantes à l'objet.</returns>
int Destroyable::getLife() const
{
	return lifePts;
}

/// <summary>
/// Endommage l'objet d'un certain nombre de points de vie.
/// </summary>
/// <param name="life">Le nombre de points de vie perdus par l'objet.</param>
void Destroyable::damage(const unsigned int life)
{
	// Si le dommage infligé est plus petit que les points de vie restant, on
	// enlève de la vie à l'objet; sinon, son nombre de points de vie devient 0.
	lifePts = life < lifePts ? lifePts - life : 0;
}

/// <summary>
/// Soigne l'objet d'un certain nombre de points de vie.
/// </summary>
/// <param name="life">Le nombre de points de vie gagnés par l'objet.</param>
void Destroyable::heal(const unsigned int life)
{
	// On ajoute la vie à l'objet, mais celle-ci ne peut pas dépasser
	// sa limite maximale de vie.
	lifePts = std::fmin(lifePts + life, maxLife);
}

/// <summary>
/// Remet l'objet à un certain nombre de points de vie.
/// </summary>
/// <param name="life">Le nombre de points de vie de l'objet.</param>
void Destroyable::resetLife(const unsigned int life)
{
	lifePts = life;
}