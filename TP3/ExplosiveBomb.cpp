#include "ExplosiveBomb.h"
#include "GameScene.h"

using namespace TP3;

/// <summary>
/// Crée une nouvelle <see cref="ExplosiveBomb"/>.
/// </summary>
ExplosiveBomb::ExplosiveBomb()
	: Bonus(ObjectType::EXPLOSIVE_BOMB)
{
	// Détermine une couleur de bouclier au hasard.
	int colorIndex = rand() % 3;
	color = getGameScene()->getGameColor(colorIndex);
}

/// <summary>
/// Retourne la couleur de la bombe.
/// </summary>
/// <returns>La couleur de la bombe</returns>
const sf::Color& ExplosiveBomb::getColor() const
{
	return color;
}

/// <summary>
/// Affiche la bombe.
/// </summary>
/// <param name="window">Le fenêtre sur laquelle afficher la bombe.</param>
void ExplosiveBomb::draw(sf::RenderWindow& window)
{
	RessourceManager::getInstance()->getSprite(getSpriteKey())->setColor(color);
	Bonus::draw(window);
}