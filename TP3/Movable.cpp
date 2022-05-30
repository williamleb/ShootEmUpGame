#include "Movable.h"
#include <cassert>

using namespace TP3;

const float Movable::diagonal = 0.707106781f;
const float Movable::directionVerificationThreshold = 0.5f;

/// <summary>
/// Cr�e un nouveau <see cref="Movable"/>.
/// </summary>
/// <param name="speed">La vitesse de l'objet.</param>
Movable::Movable(const GameObject::ObjectType type)
	: direction(0, 0), GameObject(type)
{
}

/// <summary>
/// D�truit un <see cref="Movable"/>.
/// </summary>
Movable::~Movable()
{
}

/// <summary>
/// Update l'objet selon le temps �coul�.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la m�thode.</param>
void Movable::update(const float deltaT)
{
	setPosition(getPosition() + (direction * speed * deltaT));
}

/// <summary>
/// Retourne la direction de l'objet.
/// </summary>
/// <returns>La direction de l'objet.</returns>
const sf::Vector2f& Movable::getDirection() const
{
	return direction;
}

/// <summary>
/// Retourne la vitesse de l'objet.
/// </summary>
/// <returns>La vitesse de l'objet.</returns>
float Movable::getSpeed() const
{
	return speed;
}

/// <summary>
/// Change la direction de l'objet.
/// </summary>
/// <param name="direction">La direction de l'objet.</param>
void Movable::setDirection(const Direction direction)
{
	this->direction = convertDirection(direction);
}

/// <summary>
/// Change la direction de l'objet.
/// </summary>
/// <param name="angle">L'angle de l'objet en radians.</param>
void Movable::setDirection(const float angle)
{
	direction.x = cos(angle);
	direction.y = sin(angle);
}

/// <summary>
/// Change la direction de l'objet.
/// </summary>
/// <param name="direction">La direction de l'objet.</param>
void Movable::setDirection(sf::Vector2f direction)
{
	// Il faut que l'hypoth�nuse de la direction soit �gale � 1 (car c'est la propri�t� speed qui influence la vitesse)
	// ou � 0 (si l'objet est immobile).
	assert(abs(1 - (direction.x * direction.x + direction.y * direction.y)) <= directionVerificationThreshold
				|| (direction.x == 0 && direction.y == 0));
	this->direction = direction;
}

/// <summary>
/// Change la vitesse de l'objet.
/// </summary>
/// <param name="speed">a vitesse de l'objet.</param>
void Movable::setSpeed(const float speed)
{
	this->speed = speed;
}

/// <summary>
/// Convertit une direction provenant de l'enum en vecteur.
/// </summary>
/// <param name="direction">La direction provenant de l'enum.</param>
/// <returns>La repr�sentation en vecteur de la direction.</returns>
sf::Vector2f Movable::convertDirection(Direction direction)
{
	sf::Vector2f convertedDirection(0, 0);

	switch (direction)
	{
	case Movable::IDLE:
		convertedDirection.x = 0;
		convertedDirection.y = 0;
		break;
	case Movable::UP:
		convertedDirection.x = 0;
		convertedDirection.y = -1;
		break;
	case Movable::UP_LEFT:
		convertedDirection.x = -diagonal;
		convertedDirection.y = -diagonal;
		break;
	case Movable::UP_RIGHT:
		convertedDirection.x = diagonal;
		convertedDirection.y = -diagonal;
		break;
	case Movable::LEFT:
		convertedDirection.x = -1;
		convertedDirection.y = 0;
		break;
	case Movable::DOWN:
		convertedDirection.x = 0;
		convertedDirection.y = 1;
		break;
	case Movable::DOWN_LEFT:
		convertedDirection.x = -diagonal;
		convertedDirection.y = diagonal;
		break;
	case Movable::DOWN_RIGHT:
		convertedDirection.x = diagonal;
		convertedDirection.y = diagonal;
		break;
	case Movable::RIGHT:
		convertedDirection.x = 1;
		convertedDirection.y = 0;
		break;
	}

	return convertedDirection;
}

/// <summary>
/// Convertit un angle en une direction.
/// </summary>
/// <param name="angle">L'angle � convertir en radians.</param>
/// <returns>La direction convertie.</returns>
sf::Vector2f Movable::convertDirection(const float angle)
{
	sf::Vector2f convertedDirection;
	convertedDirection.x = cos(angle);
	convertedDirection.y = sin(angle);
	return convertedDirection;
}