#define _USE_MATH_DEFINES

#include "GameObject.h"

#include <cmath>

using namespace TP3;

/// <summary>
/// Représente la scène de jeu qui est présentement jouée.
/// </summary>
GameScene* GameObject::gameScene = nullptr;

/// <summary>
/// Change la scène de jeu qui est présentement jouée pour tous les objets.
/// </summary>
/// <param name="gameScene">La scène de jeu présentement jouée.</param>
void GameObject::setGameScene(GameScene* gameScene)
{
	GameObject::gameScene = gameScene;
}

/// <summary>
/// Retourne la scène de jeu présentement jouée.
/// </summary>
/// <returns>La scène de jeu présentement jouée.</returns>
GameScene* GameObject::getGameScene()
{
	return GameObject::gameScene;
}

/// <summary>
/// Crée un nouveau <see cref="GameObject"/>.
/// </summary>
GameObject::GameObject(const ObjectType type)
	:position(), dimension(), collisionRect(), type(type)
{
	spriteKey = 0;
}

/// <summary>
/// Détruit le <see cref="GameObject"/>.
/// </summary>
GameObject::~GameObject()
{
}

/// <summary>
/// Affiche l'objet sur la fenêtre spécifiée.
/// </summary>
/// <param name="window">La fenêtre avec laquelle afficher l'objet.</param>
void GameObject::draw(sf::RenderWindow& window)
{
	if (spriteKey != 0)
	{
		sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
		sprite->setPosition(position);
		window.draw(*sprite);
	}
}

/// <summary>
/// Vérifie la collision entre deux objets.
/// La dimension est la position de l'objet doivent être exactes pour que cette méthode
/// fonctionne comme espéré.
/// </summary>
/// <param name="other">L'objet avec lequel vérifier la colision.</param>
/// <returns>True si les deux objets sont en collision; false sinon.</returns>
bool GameObject::collidesWith(const GameObject& other) const
{
	return collisionRect.intersects(other.collisionRect);
}

/// <summary>
/// Détermine si l'objet contient une position spécifique.
/// La dimension est la position de l'objet doivent être exactes pour que cette méthode
/// fonctionne comme espéré.
/// </summary>
/// <param name="position">La position avec laquelle vérifier la collision.</param>
/// <returns>True si l'objet contient la position; false sinon.</returns>
bool GameObject::contains(const sf::Vector2f& position) const
{
	return collisionRect.contains(position.x, position.y);
}

/// <summary>
/// Calcule la distance entre deux objets.
/// </summary>
/// <param name="other">L'objet avec lequel vérifier la distance.</param>
/// <returns>La distance entre les deux objets.</returns>
float GameObject::getDistanceWith(const GameObject& other) const
{
	return getDistanceWith(other.getPosition());
}

/// <summary>
/// Calcule la distance entre l'objet et une position.
/// </summary>
/// <param name="position">La position avec laquelle calculer la distance.</param>
/// <returns>La distance entre l'objet et la position.</returns>
float GameObject::getDistanceWith(const sf::Vector2f& position) const
{
	float xSqrdVal = (this->position.x - position.x) * (this->position.x - position.x);
	float ySqrdVal = (this->position.y - position.y) * (this->position.y - position.y);

	return sqrt(xSqrdVal + ySqrdVal);
}

/// <summary>
/// Calcule l'angle en radians entre deux objets.
/// </summary>
/// <param name="other">L'autre objet avec lequel calculer l'angle.</param>
/// <returns>L'angle en radians entre les deux objets.</returns>
float GameObject::getAngleWith(const GameObject& other) const
{
	return getAngleWith(other.getPosition());
}

/// <summary>
/// Calcule l'angle en radians entre l'objet et une position.
/// </summary>
/// <param name="position">La position avec laquelle calculer l'angle.</param>
/// <returns>L'angle en radians entrre l'objet et la position.</returns>
float GameObject::getAngleWith(const sf::Vector2f& position) const
{
	float xVal = (this->position.x - position.x);
	float yVal = (this->position.y - position.y);

	float angle = atanf(yVal / xVal);

	if (position.x < this->position.x)
	{
		angle += M_PI;
	}

	return angle;
}

/// <summary>
/// Retourne la position du centre de l'objet.
/// </summary>
/// <returns>La position du centre de l'objet.</returns>
const sf::Vector2f& GameObject::getPosition() const
{
	return position;
}

/// <summary>
/// Retourne les dimensions de l'objet.
/// </summary>
/// <returns>Les dimensions de l'objet.</returns>
const sf::Vector2f& GameObject::getDimension() const
{
	return dimension;
}

/// <summary>
/// Retourne la clé du sprite utilisé par l'objet.
/// </summary>
/// <returns>La clé du sprite utilisé par l'objet.</returns>
RessourceManager::key GameObject::getSpriteKey() const
{
	return spriteKey;
}

/// <summary>
/// Gets the type.
/// </summary>
/// <returns></returns>
GameObject::ObjectType GameObject::getType() const
{
	return type;
}

/// <summary>
/// Change la position du centre de l'objet.
/// </summary>
/// <param name="position">La position du centre de l'objet.</param>
void GameObject::setPosition(const sf::Vector2f& position)
{
	this->position = position;
	computeCollisionRect();
}

/// <summary>
/// Change la position du centre de l'objet.
/// </summary>
/// <param name="posX">La position en x du centre de l'objet.</param>
/// <param name="posY">La position en y du centre de l'objet.</param>
void GameObject::setPosition(const float posX, const float posY)
{
	position.x = posX;
	position.y = posY;
	computeCollisionRect();
}

/// <summary>
/// Change les dimensions de l'objet.
/// </summary>
/// <param name="dimension">Les dimensions de l'objet.</param>
void GameObject::setDimension(const sf::Vector2f& dimension)
{
	this->dimension = dimension;
	computeCollisionRect();
}

/// <summary>
/// Change les dimensions de l'objet.
/// </summary>
/// <param name="width">La largeur de l'objet.</param>
/// <param name="height">La hauteur de l'objet.</param>
void GameObject::setDimension(const float width, const float height)
{
	dimension.x = width;
	dimension.y = height;
	computeCollisionRect();
}

/// <summary>
/// Change la clé du sprite utilisé par l'objet.
/// </summary>
/// <param name="spriteKey">La clé du sprite utilisé par l'objet.</param>
void GameObject::setSpriteKey(const RessourceManager::key spriteKey)
{
	this->spriteKey = spriteKey;
}

/// <summary>
/// Change le retangle de collision dépendamment des attributs de l'objet.
/// </summary>
void GameObject::computeCollisionRect()
{
	collisionRect.left = position.x - (dimension.x / 2);
	collisionRect.top = position.y - (dimension.y / 2);
	collisionRect.width = dimension.x;
	collisionRect.height = dimension.y;
}

/// <summary>
/// Détermine si l'objet est un ennemi.
/// </summary>
/// <returns>true si l'objet est un ennemi; false sinon.</returns>
bool GameObject::isEnemy()
{
	return isEnemy(type);
}

/// <summary>
/// Détermine si le type d'objet est une ennemi.
/// </summary>
/// <param name="type">Le type d'objet à vérifier.</param>
/// <returns>true si le type d'objet est un ennemi; false sinon.</returns>
bool GameObject::isEnemy(const ObjectType type)
{
	return type == ENEMI
		|| type == TURRET
		|| type == STALKER
		|| type == SHADOW
		|| type == TROOPER
		|| type == FOLLOWED
		|| type == FOLLOWER
		|| type == CRUSHER
		|| type == CARRIER;
}

/// <summary>
/// Détermine si l'objet est un projectile.
/// </summary>
/// <returns>true si l'objet est un projectile; false sinon. </returns>
bool GameObject::isProjectile()
{
	return isProjectile(type);
}

/// <summary>
/// Détermine si le type d'objet est un projectile.
/// </summary>
/// <param name="type">Le type d'objet à vérifier.</param>
/// <returns>true si le type d'objet est un projectile d'ennemi; false sinon.</returns>
bool GameObject::isProjectile(const ObjectType type)
{
	return type == BEAM
		|| type == PLASMA_BALL
		|| type == SLASH
		|| type == TWIST
		|| isEnemyProjectile(type);
}

/// <summary>
/// Détermine si l'objet est un projectile d'ennemi.
/// </summary>
/// <returns>true si l'objet est un projectile d'ennemi; false sinon. </returns>
bool GameObject::isEnemyProjectile()
{
	return isEnemyProjectile(type);
}

/// <summary>
/// Détermine si le type d'objet est un projectile d'ennemi.
/// </summary>
/// <param name="type">Le type d'objet à vérifier.</param>
/// <returns>true si le type d'objet est un projectile d'ennemi; false sinon.</returns>
bool GameObject::isEnemyProjectile(const ObjectType type)
{
	return type == LAZER
		|| type == PROJECTILE_TURRET
		|| type == ENERGY_BALL
		|| type == RED_LAZER;

}

/// <summary>
/// Détermine si l'objet est un bonus.
/// </summary>
/// <returns>true si l'objet est un bonus; false sinon. </returns>
bool GameObject::isBonus()
{
	return isBonus(type);
}

/// <summary>
/// Détermine si le type d'objet est un bonus.
/// </summary>
/// <param name="type">Le type d'objet à vérifier.</param>
/// <returns>true si le type d'objet est un bonus; false sinon.</returns>
bool GameObject::isBonus(const ObjectType type)
{
	return type == SHIELD_ADDER 
		|| type == ELECTRO_BOMB 
		|| type == EXPLOSIVE_BOMB 
		|| type == POINTS_MULTIPLICATOR
		|| type == OPTION_ADDER
		|| isWeaponAdder(type);
}

/// <summary>
/// Détermine si l'objet est un bonus d'ajout d'arme.
/// </summary>
/// <returns>true si l'objet est un bonus d'ajout d'arme; false sinon. </returns>
bool GameObject::isWeaponAdder()
{
	return isBonus(type);
}

/// <summary>
/// Détermine si le type d'objet est un bonus d'ajout d'arme.
/// </summary>
/// <param name="type">Le type d'objet à vérifier.</param>
/// <returns>true si le type d'objet est un bonus d'ajout d'arme; false sinon.</returns>
bool GameObject::isWeaponAdder(const ObjectType type)
{
	return type == DOUBLE_BLASTER_ADDER
		|| type == SIDE_BLASTER_ADDER
		|| type == SLASHER_ADDER
		|| type == TRI_SHOOTER_ADDER
		|| type == TWISTED_SHOOTER_ADDER;
}

/// <summary>
/// Détermine si l'objet est un cargo.
/// </summary>
/// <returns>true si l'objet est un cargo; false sinon. </returns>
bool GameObject::isCargo()
{
	return isCargo(type);
}

/// <summary>
/// Détermine si le type d'objet est un cargo.
/// </summary>
/// <param name="type">Le type d'objet à vérifier.</param>
/// <returns>true si le type d'objet est un cargo; false sinon.</returns>
bool GameObject::isCargo(const ObjectType type)
{
	return type == FOLLOWED_CARGO
		|| type == TROOPER_CARGO;
}