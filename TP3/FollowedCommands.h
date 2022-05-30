#pragma once
#include <SFML\Graphics.hpp>

namespace TP3
{
	class FollowEntity;
	
	/// <summary>
	/// Commande de base pour un objet de type FollowEntity.
	/// </summary>
	class FollowedCommand_Base
	{
	public:
		sf::Time whenHappened;

		FollowedCommand_Base(const sf::Time& whenHappened);
		virtual void execute(FollowEntity* entity) const = 0;
	};

	/// <summary>
	/// Commande de changement de direction pour un objet de type FollowEntity.
	/// </summary>
	class FollowedCommand_ChangeDirection : public FollowedCommand_Base
	{
	public:
		sf::Vector2f direction;

		FollowedCommand_ChangeDirection(const sf::Vector2f& direction, const sf::Time& whenHappened);
		void execute(FollowEntity* entity) const;

		const sf::Vector2f getDirection() const;
	};

	/// <summary>
	/// Commande de tire pour un objet de type FollowEntity.
	/// </summary>
	class FollowedCommand_Fire : public FollowedCommand_Base
	{
	public:
		FollowedCommand_Fire(const sf::Time& whenHappened);
		void execute(FollowEntity* entity) const;
	};
}