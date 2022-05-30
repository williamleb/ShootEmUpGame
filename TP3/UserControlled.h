#pragma once

#include "Movable.h"
#include "Structures\stack.h"

namespace TP3
{	
	/// <summary>
	/// Un objet de jeu qui est contrôlé par le joueur.
	/// </summary>
	/// <seealso cref="Movable" />
	class UserControlled : public Movable
	{
		unsigned int positionAmongUserControlled;
		static TP3_structures::stack<UserControlled*> allUserControlled;

	public:
		UserControlled(const GameObject::ObjectType type);
		virtual ~UserControlled();

		static const UserControlled* getLastUserControlled();

		// Commandes ---------------------------------------------------------		
		virtual void changeDirection(const sf::Vector2f direction) = 0;
		virtual void fire() = 0;

	protected:
		static void addUserControlled(UserControlled* newUserControlled);
		static void removeLastUserControlled();

		bool isLast() const;
		unsigned int getPositionAmongUserControlled() const;
	};
}