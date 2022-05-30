#include "ShieldAdder.h"
#include "GameScene.h"
#include "RessourceManager.h"

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="ShieldAdder"/>.
/// </summary>
ShieldAdder::ShieldAdder()
	: Bonus(GameObject::SHIELD_ADDER)
{
	// Détermine une couleur de bouclier au hasard.
	int colorIndex = rand() % 3;
	color = getGameScene()->getGameColor(colorIndex);
}

/// <summary>
/// Retourne la couleur du bouclier ajouté par le bonus.
/// </summary>
/// <returns>La couleur du bouclier ajouté par le bonus.</returns>
const sf::Color& ShieldAdder::getColor() const
{
	return color;
}

/// <summary>
/// Afficher le bonus.
/// </summary>
/// <param name="window">La fenêtre dans laquelle afficher le bonus.</param>
void ShieldAdder::draw(sf::RenderWindow& window)
{
	RessourceManager::getInstance()->getSprite(getSpriteKey())->setColor(color);
	Bonus::draw(window);
}