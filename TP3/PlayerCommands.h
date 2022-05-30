#pragma once
#include <SFML\Graphics.hpp>

namespace TP3
{
	class UserControlled;

	/// <summary>
	/// Commande de base pour un objet de type UserControlled.
	/// </summary>
	class PlayerCommand_Base
	{
	public:
		sf::Time whenHappened;
		
		PlayerCommand_Base(const sf::Time& whenHappened);
		virtual void execute(UserControlled* player) const = 0;
	};

	/// <summary>
	/// Commande de changement de direction pour un objet de type UserControlled.
	/// </summary>
	class PlayerCommand_ChangeDirection : public PlayerCommand_Base
	{
	public:
		sf::Vector2f direction;
		
		PlayerCommand_ChangeDirection(const sf::Vector2f& direction, const sf::Time& whenHappened);
		void execute(UserControlled* player) const;

		const sf::Vector2f getDirection() const;
	};

	/// <summary>
	/// Commande de tire pour un objet de type UserControlled.
	/// </summary>
	class PlayerCommand_Fire : public PlayerCommand_Base
	{		
	public:
		PlayerCommand_Fire(const sf::Time& whenHappened);
		void execute(UserControlled* player) const;
	};
}