#pragma once

#include "Trooper.h"
#include "FollowedInputs.h"
#include "FollowEntity.h"
#include "Structures\list.h"
#include "Follower.h"

namespace TP3
{	
	/// <summary>
	/// Le Followed est un ennemi invisible et invincible qui reproduit les mouvement d'un Trooper.
	/// Il est suivit par des Follower qui, eux, peuvent causer du dommage au joueur et se détruire.
	/// </summary>
	/// <seealso cref="Trooper" />
	/// <seealso cref="FollowEntity" />
	class Followed : public Trooper, public FollowEntity
	{
	private:
		const int MS_BEFORE_COMMAND_REMOVAL = 3000;

		const int NBR_MAX_FOLLOWER = 5;

		FollowedInputs inputs;

		TP3_structures::list<Follower*> allCurrentFollowers;
	public:
		Followed();
		~Followed();

		void update(const float deltaT);

		void fire();

		void reset();

		void damage(const unsigned int life);
		void damage(const unsigned int life, const sf::Color& dammageColor);

		void activate();
		void activate(const sf::Vector2f& position);
		void deactivate();

		void draw(sf::RenderWindow& window);

		unsigned int addFollower(Follower* follower);
		void removeFollower(Follower* follower);

		void changeDirection(const sf::Vector2f direction);
		void fireCommand();

		FollowedInputs& getInputs();
	};
}