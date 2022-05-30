#pragma once

#include "Movable.h"
#include "Activatable.h"
#include "RessourceManager.h"
#include "Structures\list.h"
#include "BitmaskManager.h"

namespace TP3
{	
	/// <summary>
	/// Représente un élément de décors qui agit en tant qu'obstacle pour le joueur.
	/// </summary>
	/// <seealso cref="Movable" />
	/// <seealso cref="Activatable" />
	class BoardObstacle : public Movable, public Activatable
	{		
		struct CollisionBox;

		/// <summary>
		/// Correspond à la position depuis le coin supérieur droit du board auquel est associé l'obstacle.
		/// </summary>
		sf::Vector2f positionOnBoard;

		TP3_structures::list<CollisionBox*>allCollisionBoxes;

		RessourceManager::key textureKey;

		static RessourceManager::key playerTextureKey;

		BitmaskManager bitmasks;

	public:
		static const int OBSTACLE_DAMMAGE = 2;

		BoardObstacle(const float width, const float height, const RessourceManager::key spriteKey, const RessourceManager::key textureKey);
		~BoardObstacle();

		void activate();
		void activate(const sf::Vector2f& position);

		void update(const float deltaT);
		void draw(sf::RenderWindow& window);

		bool collidesWith(const GameObject& other);
		bool contains(const sf::Vector2f& position) const;

		void addCollisionBox(const float left, const float top, const float width, const float height);

		void setPosition(const sf::Vector2f& position);
		void setPosition(const float posX, const float posY);

		// Méthodes reliées au board.
		const sf::Vector2f& getPositionOnBoard() const;
		void setPositionOnBoard(const sf::Vector2f& position);

	private:
		void replaceCollisionBoxes();

		bool collidesWithPixelPerfect(const GameObject& other, const sf::IntRect& intersection);

	public:
		static void setPlayerTextureKey(const RessourceManager::key playerTextureKey);
	};

	struct BoardObstacle::CollisionBox
	{
		sf::IntRect rect;
		sf::Vector2f pos;

		CollisionBox(const float left, const float top, const float width, const float height);
	};
}
