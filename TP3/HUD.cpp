#include "HUD.h"
#include "Sujet.h"
#include "PointsMultiplicator.h"
#include <sstream>
#include "SideBlaster.h"
#include "ForwardBlaster.h"
#include "TriShooter.h"
#include "Slasher.h"
#include "DoubleBlaster.h"
#include "TwistedShooter.h"
#include "GameScene.h"
#include "ShieldAdder.h"
#include "WeaponAdder.h"

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="HUD"/>.
/// </summary>
/// <param name="spriteKey">Le sprite du HUD.</param>
/// <param name="shieldSpriteKey">Le sprite pour la représentation des boucliers.</param>
/// <param name="shieldSpriteKey">Le sprite pour les multiplicateurs de score.</param>
/// <param name="font">La police utilisée par le HUD.</param>
HUD::HUD(const RessourceManager::key spriteKey, const RessourceManager::key shieldSpriteKey, const RessourceManager::key multiplierSpriteKey, const RessourceManager::key shieldTextKey, const RessourceManager::key weaponTextKey, const RessourceManager::key scoreTextKey, const RessourceManager::key lifeTextKey)
	:GameObject(ObjectType::HUD), shieldSpriteKey(shieldSpriteKey), multiplierSpriteKey(multiplierSpriteKey), shieldTextKey(shieldTextKey), weaponTextKey(weaponTextKey), scoreTextKey(scoreTextKey), lifeTextKey(lifeTextKey),
	score(0), multiplierRect(0, 0, MULTIPLIER_WIDTH, MULTIPLIER_HEIGHT), playerLife(0)
{
	setSpriteKey(spriteKey);
	currentWeapon = allWeaponBoxes.begin();
}

/// <summary>
/// Détruit le <see cref="HUD"/>.
/// </summary>
HUD::~HUD()
{
	for (Multiplier* multiplier : allMultipliers)
	{
		delete multiplier;
	}

	for (WeaponBox* weaponBox : allWeaponBoxes)
	{
		delete weaponBox->getWeapon();
		delete weaponBox;
	}

	for (ShieldBox* shieldBox : allShieldBoxes)
	{
		delete shieldBox;
	}

}

/// <summary>
/// Affiche le HUD sur la fenêtre spécifiée.
/// </summary>
/// <param name="window">La fenêtre avec laquelle afficher le HUD.</param>
void HUD::draw(sf::RenderWindow& window)
{
	GameObject::draw(window);

	// Le texte de score.
	sf::Text* text = RessourceManager::getInstance()->getText(scoreTextKey);
	std::stringstream scoreStreamStream;
	scoreStreamStream << score;
	text->setPosition(getPosition() + sf::Vector2f(SCORE_POS_X, SCORE_POS_Y));
	std::string scoreString = scoreStreamStream.str();
	while (scoreString.length() != NBR_CHARACTERS_IN_SCORE)
	{
		scoreString.insert(0, "0");
	}
	text->setString(scoreString);
	window.draw(*text);

	// Le texte de vie.
	text = RessourceManager::getInstance()->getText(lifeTextKey);// TODO: Changer la couleur s'il a le maximum de vie.
	std::stringstream lifeStringStream;
	lifeStringStream << playerLife;
	text->setPosition(getPosition() + sf::Vector2f(LIFE_POS_X, LIFE_POS_Y));
	std::string lifeString = lifeStringStream.str();
	text->setString(lifeString);
	window.draw(*text);
	
	// Le multiplicateur.
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(multiplierSpriteKey);
	int nbrOfMultiplicators = allMultipliers.size();
	multiplierRect.left = nbrOfMultiplicators * MULTIPLIER_WIDTH;
	sprite->setTextureRect(multiplierRect);
	sprite->setPosition(getPosition() + sf::Vector2f(MULTIPLIER_POS_X, MULTIPLIER_POS_Y));
	window.draw(*sprite);


	// Tous les WeaponBoxes.
	unsigned int positionInList = 0;
	for (WeaponBox* weaponBox : allWeaponBoxes)
	{
		weaponBox->draw(window, 
			getPosition() + sf::Vector2f(WEAPONBOX_LIST_POS_X, WEAPONBOX_LIST_POS_Y) + sf::Vector2f(positionInList * WeaponBox::WEAPONBOX_WIDTH + 10, 10));
		positionInList++;
	}

	// Tous les ShieldBoxes.
	int posX = SHIELD_BOX_NBR_SHIELD_X - 1;
	int posY = 0;
	for (TP3_structures::list<ShieldBox*>::reverse_iterator i = allShieldBoxes.rbegin(); i != allShieldBoxes.rend(); ++i)
	{
		(*i)->draw(window, 
			getPosition() + sf::Vector2f(SHIELD_BOX_POS_X, SHIELD_BOX_POS_Y) + sf::Vector2f(posX * ShieldBox::SHIELD_WIDTH, posY * ShieldBox::SHIELD_HEIGHT));
		++posY;

		if (posY >= SHIELD_BOX_NBR_SHIELD_Y)
		{
			posY = 0;
			--posX;

			if (posX < 0)
			{
				break;
			}
		}
	}
}

/// <summary>
/// Change la vie affichée.
/// </summary>
/// <param name="life">La vie du joueur.</param>
void HUD::setLife(const unsigned int life)
{
	playerLife = life;
}

/// <summary>
/// Change la vie affichée pour le dernier bouclier.
/// </summary>
/// <param name="life">La vie du dernier bouclier du joueur.</param>
void HUD::setLastShieldLife(const unsigned int life)
{
	if (!allShieldBoxes.empty())
	{
		allShieldBoxes.back()->changeLife(life);
	}
}

/// <summary>
/// Met à jour le HUD.
/// </summary>
/// <param name="deltaT">Le temps en secondes depuis le dernier appel d'update.</param>
void HUD::update(const float deltaT)
{
	// Si on a des multiplicateurs...
	if (!allMultipliers.empty())
	{
		TP3_structures::list<Multiplier*> multipliersToRemove;

		// On les updates.
		for (TP3_structures::list<Multiplier*>::iterator i = allMultipliers.begin(); i != allMultipliers.end(); i++)
		{
			// Si leur durée de vie est finie, on les enlève.
			if ((*i)->update(deltaT))
			{
				multipliersToRemove.push_back(*i);
			}
		}

		for (TP3_structures::list<Multiplier*>::iterator i = multipliersToRemove.begin(); i != multipliersToRemove.end(); i++)
		{
			delete *i;
			allMultipliers.remove(*i);
		}
	}

	TP3_structures::list<WeaponBox*> toRemove;
	for (WeaponBox* weapon : allWeaponBoxes)
	{
		if (weapon->getWeapon()->getAmmo() == 0)
		{
			toRemove.push_back(weapon);
		}
	}

	for (WeaponBox* weapon : toRemove)
	{
		removeWeapon(weapon->getWeapon()->getType());
	}
}

/// <summary>
/// Ajoute une arme.
/// </summary>
/// <param name="type">Le type d'arme à ajouter.</param>
void HUD::addWeapon(const Weapon::WeaponType type)
{
	if (currentWeapon != allWeaponBoxes.end())
	{
		(*currentWeapon)->unselect();
	}
	bool sameTypeFound = false;
	for (WeaponBox* other : allWeaponBoxes)
	{
		// Si on trouve le même type d'arme dans la liste des armes...
		if (type == other->getWeapon()->getType())
		{
			// On ajoute seulement des munitions à l'arme dans la liste.
			sameTypeFound = true;
			other->getWeapon()->addDefaultAmmo();
		}
	}

	// Si l'arme ammassée est unique...
	if (!sameTypeFound)
	{
		// On l'ajoute à la liste.
		Weapon* newWeapon = nullptr;
		std::string weaponName = "";
		switch (type)
		{
		case Weapon::WeaponType::FORWARD_BLASTER:
			newWeapon = new ForwardBlaster();
			weaponName = "Forward";
			break;
		case Weapon::WeaponType::SIDE_BLASTER:
			newWeapon = new SideBlaster();
			weaponName = "Side";
			break;
		case Weapon::WeaponType::TRI_SHOOTER:
			newWeapon = new TriShooter();
			weaponName = "Tri";
			break;
		case Weapon::WeaponType::SLASHER:
			newWeapon = new Slasher();
			weaponName = "Slash";
			break;
		case Weapon::WeaponType::DOUBLE_BLASTER:
			newWeapon = new DoubleBlaster();
			weaponName = "Double";
			break;
		case Weapon::WeaponType::TWISTED_SHOOTER:
			newWeapon = new TwistedShooter();
			weaponName = "Twisted";
			break;
		default:
			assert(false && "Le type d'arme n'a pas encore été implémentée.");
			break;
		}
		WeaponBox* newWeaponBox = new WeaponBox(newWeapon, weaponName, weaponTextKey);

		currentWeapon = allWeaponBoxes.insert(allWeaponBoxes.end(), newWeaponBox);
		getGameScene()->addUpdatable(newWeapon);
	}
	(*currentWeapon)->select();
}

/// <summary>
/// Retire une arme.
/// </summary>
/// <param name="type">Le type d'arme à ajouter.</param>
void HUD::removeWeapon(const Weapon::WeaponType type)
{
	TP3_structures::list<WeaponBox*>::iterator toDelete = allWeaponBoxes.end();
	for (TP3_structures::list<WeaponBox*>::iterator i = allWeaponBoxes.begin(); i != allWeaponBoxes.end(); ++i)
	{
		// Si on trouve le même type d'arme dans la liste des projectiles...
		if (type == (*i)->getWeapon()->getType())
		{
			// On le retire.
			toDelete = i;
			WeaponBox* weapon = *toDelete;
			break;
		}
	}

	// Si on a trouvé une arme à enlever...
	if (toDelete != allWeaponBoxes.end())
	{
		// On le fait.
		selectRightWeapon();
		weaponBoxesToDelete.push_back(*toDelete);
		getGameScene()->removeUpdatable((*toDelete)->getWeapon());
		allWeaponBoxes.erase(toDelete);
	}
}

/// <summary>
/// Supprime les armes qui ne sont pas utilisées (plus de munitions).
/// </summary>
void HUD::deleteUnusedWeapons()
{
	for (WeaponBox* weapon : weaponBoxesToDelete)
	{
		delete weapon->getWeapon();
		delete weapon;
	}
	weaponBoxesToDelete.clear();
}

/// <summary>
/// Sélectionne l'arme à la gauche de celle sélectionnée.
/// </summary>
void HUD::selectLeftWeapon()
{
	(*currentWeapon)->unselect();

	if (currentWeapon == allWeaponBoxes.begin())
	{
		currentWeapon = allWeaponBoxes.end();
	}
	--currentWeapon;

	(*currentWeapon)->select();

}

/// <summary>
/// Sélectionne l'arme à la droite de celle sélectionnée.
/// </summary>
void HUD::selectRightWeapon()
{
	(*currentWeapon)->unselect();

	++currentWeapon;

	if (currentWeapon == allWeaponBoxes.end())
	{
		currentWeapon = allWeaponBoxes.begin();
	}

	(*currentWeapon)->select();
}

/// <summary>
/// Retourne l'arme courrante.
/// </summary>
/// <returns>L'arme courrante.</returns>
Weapon* HUD::getCurrentWeapon() const
{
	return (*currentWeapon)->getWeapon();
}

/// <summary>
/// Notifie le HUD qu'un événement s'est produit.
/// </summary>
/// <param name="sujet">Le sujet qui a appelé l'événement.</param>
void HUD::notifier(Sujet* sujet)
{
	if (GameObject* object = dynamic_cast<GameObject*>(sujet))
	{
		GameObject::ObjectType type = object->getType();

		if (isEnemy(type))
		{
			// Si c'est un ennemi qui est mort, on ajoute les points.
			Enemy* enemy = dynamic_cast<Enemy*>(object);

			int points = enemy->getPoints();

			for (Multiplier* multiplier : allMultipliers)
			{
				points = multiplier->operator*(points);
			}

			this->score += points;
		}
		else if (type == POINTS_MULTIPLICATOR)
		{
			// On ajoute un multiplicateur.
			allMultipliers.push_back(new Multiplier(PointsMultiplicator::MS_OF_MULTIPLICATION));
		}
		else if (type == SHIELD_ADDER)
		{
			ShieldAdder* adder = dynamic_cast<ShieldAdder*>(object);

			// On déselectionne le dernier bouclier.
			if (!allShieldBoxes.empty())
			{
				allShieldBoxes.back()->unfirst();
			}

			// Si c'est un bonus qui ajoute un bouclier, on en ajoute une représentation dans le HUD.
			ShieldBox* newBox = new ShieldBox(shieldSpriteKey, shieldTextKey, adder->getColor());
			newBox->first();
			allShieldBoxes.push_back(newBox);
		}
		else if (type == PLAYER)
		{
			// Si c'est le joueur qui a perdu un bouclier, on enlève le dernier bouclier.
			delete allShieldBoxes.back();
			allShieldBoxes.pop_back();

			// On sélectionne le dernier bouclier.
			if (!allShieldBoxes.empty())
			{
				allShieldBoxes.back()->first();
			}
		}
		else if (GameObject::isWeaponAdder(type))
		{
			// Si c'est un bonus qui ajoute une arme, on ajoute l'arme.
			WeaponAdder* weaponAdder = dynamic_cast<WeaponAdder*>(object);

			addWeapon(weaponAdder->getWeapon());
		}
	}
}

/// <summary>
/// Retourne le score du joueur.
/// </summary>
/// <returns>Le score du joueur.</returns>
unsigned int HUD::getScore()
{
	return score;
}

// Class HUD::WeaponBox ---------------------------------------------------------------------------
const sf::Color HUD::WeaponBox::unselectedColor = sf::Color(57, 73, 171);
const sf::Color HUD::WeaponBox::selectedColor = sf::Color(48, 79, 254);

/// <summary>
/// Crée un nouveau <see cref="WeaponBox"/>.
/// </summary>
/// <param name="weapon">L'arme contenu dans la box.</param>
/// <param name="weaponName">Le nom de l'arme à afficher.</param>
/// <param name="weaponTextKey">La clé du texte pour afficher le nom de l'arme.</param>
HUD::WeaponBox::WeaponBox(Weapon* weapon, const std::string& weaponName, const RessourceManager::key weaponTextKey)
	: weapon(weapon), weaponName(weaponName), weaponTextKey(weaponTextKey), selected(false)
{
	shape.setFillColor(unselectedColor);
	shape.setSize(sf::Vector2f(WEAPONBOX_WIDTH, WEAPONBOX_HEIGHT));
}

/// <summary>
/// Sélectionne l'arme.
/// </summary>
void HUD::WeaponBox::select()
{
	shape.setFillColor(selectedColor);
	selected = true;
}

/// <summary>
/// Déselectionne l'arme.
/// </summary>
void HUD::WeaponBox::unselect()
{
	shape.setFillColor(unselectedColor);
	selected = false;
}

/// <summary>
/// Détermine si l'arme est sélectionnée.
/// </summary>
/// <returns>true si l'arme est sélectionnée; false sinon.</returns>
bool HUD::WeaponBox::isSelected() const
{
	return selected;
}

/// <summary>
/// Affiche l'arme dans le HUD.
/// </summary>
/// <param name="window">La fenêtre avec laquelle afficher.</param>
/// <param name="position">La position à laquelle afficher.</param>
void HUD::WeaponBox::draw(sf::RenderWindow& window, const sf::Vector2f& position)
{
	// Le fond.
	shape.setPosition(position);
	if (selected)
	{
		shape.setFillColor(selectedColor);
	}
	else
	{
		shape.setFillColor(unselectedColor);
	}
	window.draw(shape);

	// Le texte.
	sf::Text* text = RessourceManager::getInstance()->getText(weaponTextKey);
	
	std::stringstream string;
	string << weaponName;
	if (weapon->getAmmo() != Weapon::INFINITE_AMMO)
	{
		string << ": " << weapon->getAmmo();
	}

	text->setString(string.str());

	text->setPosition(position + sf::Vector2f(WEAPONBOX_WIDTH, WEAPONBOX_HEIGHT) * 0.5f - sf::Vector2f(text->getGlobalBounds().width, text->getGlobalBounds().height) * 0.5f);

	window.draw(*text);
}

/// <summary>
/// Retourne l'arme contenu dans la boîte.
/// </summary>
/// <returns>L'arme contenue dans la boîte.</returns>
Weapon* HUD::WeaponBox::getWeapon() const
{
	return weapon;
}

// Class HUD::ShieldBox ---------------------------------------------------------------------------
/// <summary>
/// Crée un nouveau <see cref="ShieldBox"/>.
/// </summary>
/// <param name="spriteKey">La clé de sprite pour afficher le bouclier.</param>
/// <param name="textKey">La clé de texte pour la vie du bouclier.</param>
/// <param name="color">La couleur du bouclier.</param>
HUD::ShieldBox::ShieldBox(const RessourceManager::key spriteKey, const RessourceManager::key textKey, const sf::Color& color)
	:spriteKey(spriteKey), color(color), textKey(textKey), _first(false)
{
	
}

/// <summary>
/// Change la vie du bouclier.
/// </summary>
/// <param name="life">La vie du bouclier.</param>
void HUD::ShieldBox::changeLife(const unsigned int life)
{
	this->life = life;
}

/// <summary>
/// Affiche le bouclier dans le HUD.
/// </summary>
/// <param name="window">La fenêtre avec laquelle afficher.</param>
/// <param name="position">La position à laquelle afficher.</param>
void HUD::ShieldBox::draw(sf::RenderWindow& window, const sf::Vector2f& position)
{
	// Le sprite.
	Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setColor(color);
	sprite->setPosition(position);
	window.draw(*sprite);

	// Le texte.
	std::stringstream lifeString;
	lifeString << life;
	Text* text = RessourceManager::getInstance()->getText(textKey);
	text->setString(lifeString.str());
	text->setPosition(position + sf::Vector2f(SHIELD_WIDTH, SHIELD_HEIGHT) * 0.5f - sf::Vector2f(text->getGlobalBounds().width, text->getGlobalBounds().height) * 0.5f);
	window.draw(*text);
}

/// <summary>
/// Définit que le bouclier est le premier.
/// </summary>
void HUD::ShieldBox::first()
{
	_first = true;
}

/// <summary>
/// Définit que le bouclier n'est pas le premier.
/// </summary>
void HUD::ShieldBox::unfirst()
{
	_first = false;
}

/// <summary>
/// Détermine si le bouclier est le premier.
/// </summary>
/// <returns>true si le bouclier est le premier; false sinon.</returns>
bool HUD::ShieldBox::isFirst()
{
	return _first;
}

// Class HUD::Multiplier ----------------------------------------------------------------
/// <summary>
/// Crée un nouveau <see cref="Multiplier"/>.
/// </summary>
/// <param name="lifeTime">Le temps de vie en millisecondes du multiplicateur.</param>
/// <param name="value">La valeur du multiplicateur.</param>
HUD::Multiplier::Multiplier(const unsigned int lifeTime, const int value)
	:innerTimer(sf::microseconds(0)), lifeTime(lifeTime), value(value)
{
}

/// <summary>
/// Met à jour le multiplicateur.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la méthode.</param>
/// <returns>true si la vie du bouclier est terminée; false sinon.</returns>
bool HUD::Multiplier::update(const float deltaT)
{
	innerTimer += sf::seconds(deltaT);

	if (innerTimer.asMilliseconds() >= lifeTime)
	{
		return true;
	}

	return false;
}

/// <summary>
/// Retourne la valeur de multiplication.
/// </summary>
/// <returns>La valeur de multiplication.</returns>
int HUD::Multiplier::getValue() const
{
	return value;
}

const HUD::Multiplier HUD::Multiplier::operator*(const Multiplier& right)
{
	return Multiplier(UINT16_MAX, value * right.value);
}

int HUD::Multiplier::operator*(const int right)
{
	return right * value;
}