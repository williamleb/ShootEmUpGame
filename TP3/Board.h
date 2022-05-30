#pragma once

#include "Movable.h"
#include "BoardObstacle.h"
#include "Activatable.h"
#include "RessourceManager.h"
#include "Structures\list.h"

namespace TP3
{
	/// <summary>
	/// Un board est une section d'un niveau.
	/// Elle contient des obstacles et des ennemis.
	/// </summary>
	/// <seealso cref="Movable" />
	/// <seealso cref="Activatable" />
	class Board : public Movable, public Activatable
	{
	public:
		
		struct EnemyPlacement;

		static const int BOARD_WIDTH = 1400;
		static const int BOARD_HEIGHT = 700;
	private:

		TP3_structures::list<BoardObstacle*> allObstacles;
		TP3_structures::list<EnemyPlacement*> allEnemies;

	public:		
		Board(const RessourceManager::key backgroundSpriteKey);
		~Board();

		void activate(const sf::Vector2f& position);
		void deactivate();

		void update(const float deltaT);
		void draw(sf::RenderWindow& window);

		bool collidesWith(const GameObject& other) const;
		bool contains(const sf::Vector2f& position) const;

		void addObstacle(BoardObstacle* obstacle, const sf::Vector2f& positionOnBoard);
		void addEnemy(EnemyPlacement* enemy);

		void setPosition(const sf::Vector2f& position);
		void setPosition(const float posX, const float posY);
	};

	/// <summary>
	/// Un ticket qui permet de connaître la position des ennemis qui apparaîssent sur le board.
	/// </summary>
	struct Board::EnemyPlacement
	{
		GameObject::ObjectType enemyType;
		sf::Vector2f position;

		EnemyPlacement(const GameObject::ObjectType enemyType, const sf::Vector2f& position);
		EnemyPlacement(const GameObject::ObjectType enemyType, const float posX, const float posY);

		EnemyPlacement& operator=(const EnemyPlacement& other);
	};
}