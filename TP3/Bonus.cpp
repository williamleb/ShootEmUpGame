#include "Bonus.h"
#include "GameScene.h"
#include <cassert>

using namespace TP3;

/// <summary>
/// Cr�e un nouveau <see cref="Bonus"/>.
/// </summary>
/// <param name="type">The type.</param>
Bonus::Bonus(const GameObject::ObjectType type)
	:Movable(type), picker(nullptr)
{
	assert(GameObject::isBonus(type) && "Le type de l'objet doit �tre un bonus.");
}

/// <summary>
/// D�truit un <see cref="Bonus"/>.
/// </summary>
Bonus::~Bonus()
{
}

/// <summary>
/// Active le bonus.
/// </summary>
void Bonus::activate()
{
	innerTimer = sf::microseconds(0);
	Activatable::activate();
}

/// <summary>
/// Active le bonus.
/// </summary>
/// <param name="position">La position � laquelle activer le bonus.</param>
void Bonus::activate(const sf::Vector2f& position)
{
	setPosition(position);
	activate();
}

/// <summary>
/// Met � jour le bonus.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la m�thode.</param>
void Bonus::update(const float deltaT)
{
	if (isActivated())
	{
		Movable::update(deltaT);

		innerTimer += sf::seconds(deltaT);

		// On d�sactive le bonus si �a fait assez de temps qu'il est sur le jeu.
		if (innerTimer.asMilliseconds() >= MS_LIFETIME)
		{
			deactivate();
		}

		// On d�sactive le bonus s'il sort du jeu.
		if (getPosition().x + getDimension().x * 0.5f < GameScene::GAME_LEFT)
		{
			deactivate();
		}
	}
}

/// <summary>
/// Affiche le bonus sur la fen�tre.
/// </summary>
/// <param name="window">Le fen�tre sur laquelle afficher le bonus.</param>
void Bonus::draw(sf::RenderWindow& window)
{
	if (isActivated())
	{
		Movable::draw(window);
	}
}

/// <summary>
/// Initialise le bonus.
/// Doit �tre appel� une fois avant d'utiliser le bonus.
/// </summary>
/// <param name="spriteKey">La cl� de sprite utilis�e par le bonus.</param>
/// <returns>true si l'initialisation s'est effectu�e avec succ�s; false sinon.</returns>
bool Bonus::init(RessourceManager::key spriteKey)
{
	setDirection(Movable::LEFT);
	setSpeed(GameScene::SCROLLING_SPEED);

	setSpriteKey(spriteKey);
	RessourceManager::getInstance()->getSprite(spriteKey)->setOrigin(BONUS_WIDTH / 2, BONUS_HEIGHT / 2);

	setDimension(BONUS_WIDTH, BONUS_HEIGHT);
	return true;
}

/// <summary>
/// Ramasse le bonus.
/// </summary>
/// <param name="picker">L'objet qui a rammass� le bonus.</param>
void Bonus::pick(const GameObject* picker)
{	
	if (isActivated())
	{
		this->picker = picker;

		// Apr�s avoir rammass� le bonus, on notifie les observateurs et on d�sactive le bonus.
		notifierTousLesObservateurs();
		deactivate();
	}
}

/// <summary>
/// Retourne l'objet qui a rammass� le bonus.
/// </summary>
/// <returns>L'objet qui a rammass� le bonus.</returns>
const GameObject* Bonus::getPicker() const
{
	return picker;
}