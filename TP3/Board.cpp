#include "Board.h"
#include "GameScene.h"
#include <cassert>

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="Board"/>.
/// </summary>
Board::Board(const RessourceManager::key backgroundSpriteKey)
	: Movable(GameObject::BOARD)
{
	setDirection(LEFT);
	setSpeed(GameScene::SCROLLING_SPEED);

	setSpriteKey(backgroundSpriteKey);

	if (backgroundSpriteKey != 0)
	{
		RessourceManager::getInstance()->getSprite(backgroundSpriteKey)->setOrigin(BOARD_WIDTH / 2, BOARD_HEIGHT / 2);
	}

	setDimension(BOARD_WIDTH, BOARD_HEIGHT);
}

/// <summary>
/// Détruit un <see cref="Board"/>.
/// </summary>
Board::~Board()
{
	for (BoardObstacle* obstacle : allObstacles)
	{
		delete obstacle;
	}

	for (EnemyPlacement* enemy : allEnemies)
	{
		delete enemy;
	}
}

/// <summary>
/// Active le board et tous les objets qui y sont collés.
/// </summary>
/// <param name="position">La position où activer le board.</param>
void Board::activate(const sf::Vector2f& position)
{
	Activatable::activate();
	setPosition(position);

	// Active les obstacles.
	for (BoardObstacle* obstacle : allObstacles)
	{
		obstacle->activate();
	}

	// Active les ennemis.
	sf::Vector2f topLeft = getPosition() - (getDimension() * 0.5f);
	for (EnemyPlacement* enemy : allEnemies)
	{
		getGameScene()->activateObject(enemy->enemyType, topLeft + enemy->position);
	}
}

/// <summary>
/// Désactive le board et tous ses obstacles.
/// </summary>
void Board::deactivate()
{
	Activatable::deactivate();
	for (BoardObstacle* obstacle : allObstacles)
	{
		obstacle->deactivate();
	}
}

/// <summary>
/// Update le board et tous ses obstacles.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la méthode.</param>
void Board::update(const float deltaT)
{
	if (isActivated())
	{
		Movable::update(deltaT);

		// Update les obstacles.
		for (BoardObstacle* obstacle : allObstacles)
		{
			obstacle->update(deltaT);
		}
	}
}

/// <summary>
/// Affiche le board et tous ses obstacles.
/// </summary>
/// <param name="window">La fenêtre sur laquelle afficher le board.</param>
void Board::draw(sf::RenderWindow& window)
{
	if (isActivated())
	{
		setPosition(getPosition().x, getPosition().y + 300);
		Movable::draw(window);
		setPosition(getPosition().x, getPosition().y - 300);

		for (BoardObstacle* obstacle : allObstacles)
		{
			obstacle->draw(window);
		}
	}
}

/// <summary>
/// Vérifie s'il y a une collision entre un objet et un des obstacles du board.
/// </summary>
/// <param name="other">L'objet à vérifier la collision.</param>
/// <returns>true s'il y a collision; false sinon.</returns>
bool Board::collidesWith(const GameObject& other) const
{
	bool collidesWithOneObstacle = false;

	// On vérifie la collision avec tous les objets.
	for (BoardObstacle* obstacle : allObstacles)
	{
		if (obstacle->collidesWith(other))
		{
			collidesWithOneObstacle = true;
		}
	}

	return collidesWithOneObstacle;
}

/// <summary>
/// Vérifie un des obstacles du board contient une position.
/// </summary>
/// <param name="position">La position à vérifier.</param>
/// <returns>true si un des obsttacles contient la position; false sinon.</returns>
bool Board::contains(const sf::Vector2f& position) const
{
	bool oneObstacleContainsIt = false;

	// On vérifie avec tous les obstacles.
	for (BoardObstacle* obstacle : allObstacles)
	{
		if (obstacle->contains(position))
		{
			oneObstacleContainsIt = true;
		}
	}

	return oneObstacleContainsIt;
}

/// <summary>
/// Ajoute une obstacle au board.
/// L'obstacle ajouté est complètement pris en charge par le board.
/// </summary>
/// <param name="obstacle">L'obstacle à ajouter.</param>
/// <param name="positionOnBoard">La position sur le board à ajouter.</param>
void Board::addObstacle(BoardObstacle* obstacle, const sf::Vector2f& positionOnBoard)
{
	obstacle->setPositionOnBoard(positionOnBoard);
	allObstacles.push_back(obstacle);
}

/// <summary>
/// Ajoute un ennemi au board.
/// Le ticket d'ennemi est complètement pris en charge par le board.
/// </summary>
/// <param name="enemy">Le ticket de l'ennemi à ajouter.</param>
void Board::addEnemy(EnemyPlacement* enemy)
{
	allEnemies.push_back(enemy);
}

/// <summary>
/// Change la position du board.
/// </summary>
/// <param name="position">La position.</param>
void Board::setPosition(const sf::Vector2f& position)
{
	Movable::setPosition(position);

	// On change la position de tous les obstacles.
	sf::Vector2f topLeft = getPosition() - (getDimension() * 0.5f);
	for (BoardObstacle* obstacle : allObstacles)
	{
		obstacle->setPosition(topLeft + obstacle->getPositionOnBoard());
	}
}

/// <summary>
/// Change la position du board.
/// </summary>
/// <param name="posX">La position en x.</param>
/// <param name="posY">La position en y.</param>
void Board::setPosition(const float posX, const float posY)
{
	setPosition(sf::Vector2f(posX, posY));
}

// EnemyPlacement ---------------------------------------------------------------------------------

/// <summary>
/// Crée un nouveau <see cref="EnemyPlacement"/>.
/// </summary>
/// <param name="enemyType">Le type d'ennemi.</param>
/// <param name="position">La position de l'ennemi sur le board.</param>
Board::EnemyPlacement::EnemyPlacement(const GameObject::ObjectType enemyType, const sf::Vector2f& position)
	: enemyType(enemyType), position(position)
{
	assert(GameObject::isEnemy(enemyType) || GameObject::isCargo(enemyType) && "Le type d'objet doit être un ennemi ou un cargo.");
}

/// <summary>
/// Crée un nouveau <see cref="EnemyPlacement"/>.
/// </summary>
/// <param name="enemyType">Le type d'ennemi.</param>
/// <param name="posX">La position en X de l'ennemi sur le board.</param>
/// <param name="posY">La position en Y de l'ennemi sur le board.</param>
Board::EnemyPlacement::EnemyPlacement(const GameObject::ObjectType enemyType, const float posX, const float posY)
	: enemyType(enemyType), position(sf::Vector2f(posX, posY))
{
	assert(GameObject::isEnemy(enemyType) && "Le type d'objet doit être un ennemi.");
}

/// <summary>
/// Copie un <see cref="EnemyPlacement"/>.
/// </summary>
/// <param name="other">L'autre <see cref="EnemyPlacement"/>.</param>
/// <returns>L'objet copié.</returns>
Board::EnemyPlacement& Board::EnemyPlacement::operator=(const EnemyPlacement& other)
{
	position = other.position;
	enemyType = other.enemyType;
	return *this;
}