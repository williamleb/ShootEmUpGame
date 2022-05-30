#pragma once

#include "Structures\stack.h"
#include "GameObject.h"

namespace TP3
{	
	/// <summary>
	/// Un FollowEntity est une entité qui peut être affectée par les commandes de FollowedCommands.h.
	/// </summary>
	class FollowEntity
	{
	public:
		FollowEntity();
		virtual ~FollowEntity();

		// Commandes ---------------------------------------------------------		
		virtual void changeDirection(const sf::Vector2f direction) = 0;
		virtual void fireCommand() = 0;
	};
}
