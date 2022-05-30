#include "Cargo.h"
#include "GameScene.h"
#include <cassert>

using namespace TP3;

/// <summary>
/// Crée un nouveau <see cref="Cargo"/>.
/// </summary>
/// <param name="type">Le type de Cargo à créer.</param>
/// <param name="spawnRate">Le délais entre chaque apparition d'ennemis.</param>
Cargo::Cargo(GameObject::ObjectType type, const int spawnRate)
	: Movable(type), spawnRate(spawnRate), timerSpawn(sf::microseconds(0)), Destroyable(0, CARGO_LIFE)
{
	assert(GameObject::isCargo(type) && "Le type doit en être un de cargo.");
}

/// <summary>
/// Active le Cargo.
/// </summary>
void Cargo::activate()
{
	resetLife(CARGO_LIFE);
	timerSpawn = sf::microseconds(0);
	Activatable::activate();
}

/// <summary>
/// Active le Cargo à une position spécifique.
/// </summary>
/// <param name="position">La position à laquelle activer le Cargo.</param>
void Cargo::activate(const sf::Vector2f& position)
{
	resetLife(CARGO_LIFE);
	setPosition(position);
	timerSpawn = sf::microseconds(0);
	Activatable::activate();
}

/// <summary>
/// Update l'objet selon le temps écoulé.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la méthode.</param>
void Cargo::update(const float deltaT)
{
	if (isActivated())
	{
		Movable::update(deltaT);

		if (!isDestroyed())
		{
			timerSpawn += sf::seconds(deltaT);

			// On fait apparaître des ennemis à un certain intervalle, mais seulement si
			// on est dans le jeu.
			if (timerSpawn.asMilliseconds() >= spawnRate 
				&& getPosition().x + getDimension().x * 0.5f < GameScene::GAME_LEFT + GameScene::GAME_WIDTH)
			{
				timerSpawn = sf::microseconds(0);
				spawn();
			}
		}

		// Le cargo se désactive s'il sort de la scène à gauche
		sf::Vector2f pos = getPosition();
		sf::Vector2f halfSize = getDimension() * 0.5f;
		GameScene* game = getGameScene();
		// Limites horizontales.
		if (pos.x + halfSize.x < game->GAME_LEFT)
		{
			deactivate();
		}
	}
}

/// <summary>
/// Affiche le Cargo.
/// </summary>
/// <param name="window">La fenêtre sur laquelle afficher le Cargo.</param>
void Cargo::draw(sf::RenderWindow& window)
{
	if (isActivated())
	{
		// Le Cargo s'affiche différemment selon s'il est détruit ou non.
		if (isDestroyed())
		{
			RessourceManager::getInstance()->getSprite(getSpriteKey())->setTextureRect(destroyed);
		}
		else
		{
			RessourceManager::getInstance()->getSprite(getSpriteKey())->setTextureRect(alive);
		}

		Movable::draw(window);
	}
}

/// <summary>
/// Initialise le Cargo.
/// Doit être appelé une fois avant l'utilisation du cargo.
/// </summary>
/// <param name="spriteKey">La clé du sprite utilisée par le Cargo.</param>
/// <returns>true si le Cargo s'est bien initialisé; false sinon.</returns>
bool Cargo::init(RessourceManager::key spriteKey)
{
	setDirection(Movable::Direction::LEFT);
	setSpeed(GameScene::SCROLLING_SPEED);

	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(CARGO_WIDTH / 2, CARGO_HEIGHT / 2);
	setDimension(CARGO_WIDTH, CARGO_HEIGHT);

	alive = sf::IntRect(0, 0, CARGO_WIDTH, CARGO_HEIGHT);
	destroyed = sf::IntRect(CARGO_WIDTH, 0, CARGO_WIDTH, CARGO_HEIGHT);

	return true;
}