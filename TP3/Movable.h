#pragma once

#include "GameObject.h"
#include "IUpdatable.h"

namespace TP3
{
	/// <summary>
	/// Représente un objet qui peut bouger dans le jeu.
	/// </summary>
	/// <seealso cref="GameObject" />
	class Movable : public GameObject, public IUpdatable
	{
	public:
		/// <summary>
		/// Différentes directions simplifiées que peut avoir un movable.
		/// </summary>
		enum Direction
		{
			IDLE,
			UP,
			UP_LEFT,
			UP_RIGHT,
			LEFT,
			DOWN,
			DOWN_LEFT,
			DOWN_RIGHT,
			RIGHT
		};

	private:
		/// <summary>
		/// La vitesse est exprimée en px/sec.
		/// </summary>
		float speed;

		sf::Vector2f direction;

	public:
		virtual ~Movable();
		Movable(const GameObject::ObjectType type);
		virtual void update(const float deltaT);

		const sf::Vector2f& getDirection() const;
		float getSpeed() const;

		void  setDirection(const Direction direction);
		void  setDirection(const float angle);
		void  setDirection(sf::Vector2f direction);
		void setSpeed(const float speed);

		static sf::Vector2f convertDirection(Direction direction);
		static sf::Vector2f convertDirection(const float angle);

	protected:
		static const float directionVerificationThreshold;

	private:
		// Constante qui représente racine de 2 / 2
		static const float diagonal;
	};
}