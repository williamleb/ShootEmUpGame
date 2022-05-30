#include "BoardObstacle.h"
#include "GameScene.h"
#include "BitmaskManager.h"

using namespace TP3;

RessourceManager::key BoardObstacle::playerTextureKey;

/// <summary>
/// Détermine la clé de la texture du joueur.
/// </summary>
/// <param name="playerTextureKey">Le clé de texture du joueur.</param>
void BoardObstacle::setPlayerTextureKey(const RessourceManager::key playerTextureKey)
{
	BoardObstacle::playerTextureKey = playerTextureKey;
}

/// <summary>
/// Crée un nouveau <see cref="BoardObstacle"/>.
/// </summary>
BoardObstacle::BoardObstacle(const float width, const float height, const RessourceManager::key spriteKey, const RessourceManager::key textureKey)
	: Movable(GameObject::BOARD_OBSTACLE), textureKey(textureKey)
{
	setDirection(LEFT);
	setSpeed(GameScene::SCROLLING_SPEED);

	setSpriteKey(spriteKey);
	RessourceManager::getInstance()->getSprite(spriteKey)->setOrigin(width / 2, height / 2);

	setDimension(width, height);
}

/// <summary>
/// Détruit un <see cref="BoardObstacle"/>.
/// </summary>
BoardObstacle::~BoardObstacle()
{
	for (CollisionBox* box : allCollisionBoxes)
	{
		delete box;
	}
}

/// <summary>
/// Active l'objet.
/// </summary>
void BoardObstacle::activate()
{
	Activatable::activate();
}

/// <summary>
/// Active l'objet à une position spécifique.
/// </summary>
/// <param name="position">La position à laquelle activer le joueur.</param>
void BoardObstacle::activate(const sf::Vector2f& position)
{
	Activatable::activate();
	setPosition(position);
}

/// <summary>
/// Update l'objet selon le temps écoulé.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la méthode.</param>
void BoardObstacle::update(const float deltaT)
{
	if (isActivated())
	{
		Movable::update(deltaT);
		replaceCollisionBoxes();
	}
}

/// <summary>
/// Affiche l'obstacle.
/// </summary>
/// <param name="window">La fenêtre sur laquelle afficher l'obstacle.</param>
void BoardObstacle::draw(sf::RenderWindow& window)
{
	if (isActivated())
	{

		Movable::draw(window);
	}
}

/// <summary>
/// Détermine si l'autre objet est en collision avec l'obstacle.
/// </summary>
/// <param name="other">L'autre objet.</param>
/// <returns>true si les objets sont en collision; false sinon.</returns>
bool BoardObstacle::collidesWith(const GameObject& other)
{
	bool collidesWithOneRect = false;

	// Si on n'a pas de boîtes de collisions, on test la collision normalement.
	if (allCollisionBoxes.empty())
	{
		// Une collision avec le joueur est déterminée de manière pixel-perfect.
		if (other.getType() == ObjectType::PLAYER)
		{
			sf::IntRect intersection;

			sf::IntRect otherRect(other.getPosition().x - other.getDimension().x * 0.5f, other.getPosition().y - other.getDimension().y * 0.5f,
				other.getDimension().x, other.getDimension().y);

			sf::IntRect thisRect(getPosition().x - getDimension().x * 0.5f, getPosition().y - getDimension().y * 0.5f,
				getDimension().x, getDimension().y);

			if (otherRect.intersects(thisRect, intersection))
			{
				return collidesWithPixelPerfect(other, intersection);
			}
		}
		// Les autres collisions sont régulières.
		else
		{
			return Movable::collidesWith(other);
		}
	}
	else
	{
		sf::IntRect otherRect(other.getPosition().x - other.getDimension().x * 0.5f, other.getPosition().y - other.getDimension().y * 0.5f,
			other.getDimension().x, other.getDimension().y);

		sf::IntRect intersection;
		// On vérifie la collision avec tous les objets.
		for (CollisionBox* box : allCollisionBoxes)
		{
			if (otherRect.intersects(box->rect, intersection))
			{
				// Une collision avec le joueur est déterminée de manière pixel-perfect.
				if (other.getType() == ObjectType::PLAYER || other.getType())
				{
					collidesWithOneRect = collidesWithPixelPerfect(other, intersection);
				}
				// Les autres collisions sont régulières.
				else
				{
					collidesWithOneRect = true;
				}
			}
		}
	}


	return collidesWithOneRect;
}

/// <summary>
/// Détermine si l'obstacle contient une position.
/// </summary>
/// <param name="position">La position à vérifier.</param>
/// <returns>true si l'obstacle contient la position; false sinon.</returns>
bool BoardObstacle::contains(const sf::Vector2f& position) const
{
	bool isContainedByOneRect = false;

	sf::IntRect otherRect(getPosition().x - getDimension().x * 0.5f, getPosition().y - getDimension().y * 0.5f,
		getDimension().x, getDimension().y);

	// Si on n'a pas de boîtes de collisions, on fait le test normal.
	if (allCollisionBoxes.empty())
	{
		return Movable::contains(position);
	}
	else
	{
		// On vérifie la collision avec tous les objets.
		for (CollisionBox* box : allCollisionBoxes)
		{
			if (box->rect.contains(position.x, position.y))
			{
				isContainedByOneRect = true;
			}
		}
	}

	return isContainedByOneRect;
}

/// <summary>
/// Ajoute une boîte de collision à l'obstacle.
/// Les paramètres sont relatif au coin supérieur droit de l'obstacle.
/// </summary>
void BoardObstacle::addCollisionBox(const float left, const float top, const float width, const float height)
{
	allCollisionBoxes.push_back(new CollisionBox(left, top, width, height));
}

/// <summary>
/// Change la position de l'obstacle.
/// </summary>
/// <param name="position">La position de l'obstacle.</param>
void BoardObstacle::setPosition(const sf::Vector2f& position)
{
	Movable::setPosition(position);
	replaceCollisionBoxes();
}

/// <summary>
/// Change la position de l'obstacle.
/// </summary>
/// <param name="posX">La position en x de l'obstacle.</param>
/// <param name="posY">La position en y de l'obstacle.</param>
void BoardObstacle::setPosition(const float posX, const float posY)
{
	Movable::setPosition(posX, posY);
	replaceCollisionBoxes();
}

/// <summary>
/// Replace les boîtes de collisions selon la position de l'obstacle.
/// </summary>
void BoardObstacle::replaceCollisionBoxes()
{
	sf::Vector2f topLeft = getPosition() - (getDimension() * 0.5f);
	for (CollisionBox* box : allCollisionBoxes)
	{
		box->rect.left = topLeft.x + box->pos.x;
		box->rect.top = topLeft.y + box->pos.y;
	}
}

/// <summary>
/// Retourne la position de l'objet sur la board.
/// </summary>
/// <returns>La position de l'objet sur la board.</returns>
const sf::Vector2f& BoardObstacle::getPositionOnBoard() const
{
	return positionOnBoard;
}

/// <summary>
/// Change la position de l'objet sur la board.
/// </summary>
/// <param name="position">La position de l'objet sur la board.</param>
void BoardObstacle::setPositionOnBoard(const sf::Vector2f& position)
{
	positionOnBoard = position;
}

/// <summary>
/// Détermine s'il y a une collision pixel-perfect entre l'obstacle et l'objet.
/// </summary>
/// <param name="other">L'autre objet.</param>
/// <param name="intersection">Le rectangle d'instersection entre l'objet et l'obstacle.</param>
/// <returns>true s'il y a une collision pixel-perfect; false sinon.</returns>
bool BoardObstacle::collidesWithPixelPerfect(const GameObject& other, const sf::IntRect& intersection)
{
	// Algorithme pris de l'exemple de projet "Défilement et composite" du cours
	// de programmation de jeux vidéo III
	// Modifié par William Lebel

	ObjectType type = other.getType();

	RessourceManager* ressourceManager = RessourceManager::getInstance();

	sf::Sprite* thisSprite = ressourceManager->getSprite(getSpriteKey());
	thisSprite->setPosition(getPosition());
	sf::Sprite* autreSprite = ressourceManager->getSprite(other.getSpriteKey());

	IntRect thisSubRect = thisSprite->getTextureRect();
	IntRect autreSubRect = autreSprite->getTextureRect();

	sf::Texture* thisTexture = ressourceManager->getTexture(textureKey);
	sf::Texture* autreTexture = ressourceManager->getTexture(playerTextureKey);

	unsigned char* mask1 = bitmasks.getMask(thisTexture);
	unsigned char* mask2 = bitmasks.getMask(autreTexture);

	// Loop through our pixels
	for (int i = intersection.left; i < intersection.left + intersection.width; i++)
	{
		for (int j = intersection.top; j < intersection.top + intersection.height; j++)
		{

			Vector2f thisVector = thisSprite->getInverseTransform().transformPoint(i, j);
			Vector2f autreVector = autreSprite->getInverseTransform().transformPoint(i, j);

			// Make sure pixels fall within the sprite's subrect
			if (thisVector.x > 0 && thisVector.y > 0 && autreVector.x > 0 && autreVector.y > 0 &&
				thisVector.x < thisSubRect.width && thisVector.y < thisSubRect.height &&
				autreVector.x < autreSubRect.width && autreVector.y < autreSubRect.height)
			{
				if (bitmasks.getPixel(mask1, thisTexture, (int)(thisVector.x) + thisSubRect.left, (int)(thisVector.y) + thisSubRect.top) > 150 &&
					bitmasks.getPixel(mask2, autreTexture, (int)(autreVector.x) + autreSubRect.left, (int)(autreVector.y) + autreSubRect.top) > 150)
					return true;

			}
		}
	}

	return false;
}

// BoardObstacle::CollisionBox --------------------------------------------------------------------
/// <summary>
/// Crée un nouveau <see cref="CollisionBox"/>.
/// </summary>
BoardObstacle::CollisionBox::CollisionBox(const float left, const float top, const float width, const float height)
	:rect(left, top, width, height), pos(left, top)
{
}

