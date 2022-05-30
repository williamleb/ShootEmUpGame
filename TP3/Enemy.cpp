#include "Enemy.h"
#include "GameScene.h"
#include <cassert>
#include "RessourceManager.h"
#include "ExplosiveBomb.h"
#include "ElectroBomb.h"

using namespace TP3;

/// <summary>
/// Représente le joueur qui utilise les armes.
/// </summary>
Player* Enemy::player = nullptr;

/// <summary>
/// Change le joueur qui utilise les armes.
/// </summary>
/// <param name="gameScene">Le joueur qui utilise les armes.</param>
void Enemy::setPlayer(Player* player)
{
	Enemy::player = player;
}

/// <summary>
/// Retourne le joueur qui utilise les armes.
/// </summary>
/// <returns>Le joueur qui utilise les armes.</returns>
Player* Enemy::getPlayer()
{
	return Enemy::player;
}

/// <summary>
/// Crée un nouvel <see cref="Enemy"/>.
/// </summary>
/// <param name="type">Le type d'ennemi.</param>
/// <param name="fireRate">Le délais en millisecondes entre chaque tir.</param>
/// <param name="defaultLife">Les points de vie par défaut de l'ennemi.</param>
/// <param name="defaultSpeed">La vitesse par défaut de l'ennemi.</param>
/// <param name="pointsGiven">Le nombre de points données au joueur à la destruction de l'ennemi.</param>
/// <param name="collisionDamage">Le nombre de points de vie que fait subir l'ennemi lors d'une collision.</param>
Enemy::Enemy(const ObjectType type, const int fireRate, const unsigned int defaultLife, const float defaultSpeed, const int pointsGiven, const int collisionDamage)
	: Movable(type), Destroyable(defaultLife, defaultLife), fireRateMS(fireRate), defaultLife(defaultLife), defaultSpeed(defaultSpeed), pointsGivenWhenDestroyed(pointsGiven), state(Deactivated), collisionDamage(collisionDamage),
	isDisabled(false), timerDisability(sf::microseconds(0))
{
	assert(isEnemy(type) && "Le type doit en être un d'ennemi.");

	reset();
}

/// <summary>
/// Détruit un <see cref="Enemy"/>.
/// </summary>
Enemy::~Enemy()
{
}

/// <summary>
/// Retourne le délais en millisecondes entre chaque tir.
/// </summary>
/// <returns>Le délais en millisecondes entre chaque tir.</returns>
unsigned int Enemy::getFireRate()
{
	return fireRateMS;
}

/// <summary>
/// Retourne les points donnés par l'ennemi à sa destruction.
/// </summary>
/// <returns>Les points donnés par l'ennemi à sa destruction.</returns>
int Enemy::getPoints()
{
	return pointsGivenWhenDestroyed;
}

/// <summary>
/// Retourne l'état de l'ennemi.
/// </summary>
/// <returns>L'état de l'ennemi.</returns>
Enemy::State Enemy::getState()
{
	return state;
}

/// <summary>
/// Retourne la couleur de l'ennemi.
/// </summary>
/// <returns>La couleur de l'ennemi.</returns>
const sf::Color& Enemy::getColor() const
{
	return color;
}

/// <summary>
/// Retourne les dégats infligés par l'ennemi après une collision.
/// </summary>
int Enemy::getCollisionDamage() const
{
	return collisionDamage;
}

/// <summary>
/// Change l'état de l'ennemi.
/// </summary>
/// <param name="state">Le nouvel état de l'ennemi.</param>
void Enemy::setState(const State state)
{
	this->state = state;
}

/// <summary>
/// Endommage l'ennemi.
/// </summary>
/// <param name="life">Le nombre de points de vie perdus par l'ennemi.</param>
void Enemy::damage(const unsigned int life)
{
	if (state == Moving)
	{
		Destroyable::damage(life);

		// Si l'ennemi vient d'être détruit, on le désactive et on notifie les observateur de sa mort.
		if (isDestroyed())
		{
			state = Destroyed;
			deactivate();
			notifierTousLesObservateurs();
		}
	}
}

/// <summary>
/// Endommage l'ennemi avec une couleur spéficique.
/// </summary>
/// <param name="life">Le nombre de points de vie perdus par l'ennemi.</param>
/// <param name="dammageColor">La couleur de ce qui endommage l'ennemi.</param>
void Enemy::damage(const unsigned int life, const sf::Color& dammageColor)
{
	// Endommage l'ennemi seulement si la couleur de ce qui a fait le dommage n'est pas la même que la sienne.
	if (dammageColor != this->color)
	{
		damage(life);
	}
}

/// <summary>
/// Active l'ennemi.
/// </summary>
void Enemy::activate()
{
	reset();
	Activatable::activate();
}

/// <summary>
/// Active l'ennemi à une position spécifique.
/// </summary>
/// <param name="position">La position à laquelle activer l'ennemi.</param>
void Enemy::activate(const sf::Vector2f& position)
{
	reset();
	setPosition(position);
	Activatable::activate();
}

/// <summary>
/// Désactive l'ennemi.
/// </summary>
void Enemy::deactivate()
{
	Activatable::deactivate();

	if (state != Destroyed)
	{
		state = Deactivated;
	}
}

/// <summary>
/// Notifie l'ennemi qu'un événement s'est produit.
/// </summary>
/// <param name="sujet">Le sujet qui a appelé l'événement.</param>
void Enemy::notifier(Sujet* sujet)
{
	if (GameObject* object = dynamic_cast<GameObject*>(sujet))
	{
		GameObject::ObjectType type = object->getType();

		// Si c'est une bombe explosive, l'ennemi perds de la vie plus il est près.
		if (type == GameObject::EXPLOSIVE_BOMB)
		{
			ExplosiveBomb* bomb = dynamic_cast<ExplosiveBomb*>(object);

			float distanceX = abs(object->getPosition().x - getPosition().x);
			float distanceY = abs(object->getPosition().y - getPosition().y);

			float distance = sqrtf(distanceX * distanceX + distanceY * distanceY);
			float dommage = ExplosiveBomb::MAX_DAMAGE - (distance / 50);

			if (dommage < 0)
			{
				dommage = 0;
			}

			damage(dommage, bomb->getColor());
		}
		// Si c'est une bombe électromagnétique, l'ennemi perd sa capacité à tirer pendant quelques instants.
		else if (type == GameObject::ELECTRO_BOMB)
		{
			ElectroBomb* bomb = dynamic_cast<ElectroBomb*>(object);

			if (bomb->getPicker()->getType() == GameObject::ObjectType::PLAYER)
			{
				isDisabled = true;
				timerDisability = sf::milliseconds(ElectroBomb::MS_OF_DISABILITY);
			}
		}
	}
}

/// <summary>
/// Update l'ennemi selon le temps écoulé.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la méthode.</param>
void Enemy::update(const float deltaT)
{
	if (isActivated())
	{
		if (isDisabled)
		{
			timerDisability -= sf::seconds(deltaT);

			if (timerDisability.asMilliseconds() <= 0)
			{
				isDisabled = false;
			}
		}

		// Si l'ennemi est en train d'apparaître...
		if (state == Spawning)
		{
			// S'il est entré dans le jeu...
			if (getPosition().x - getDimension().x * 0.5f < GameScene::GAME_LEFT + GameScene::GAME_WIDTH)
			{
				// On le fait changer d'état pour qu'il ait son propre comportement.
				state = Moving;
				setSpeed(defaultSpeed);
			}
		}
		else if (state == Moving)
		{
			// Il se désactive s'il sort de l'écran par la gauche ou par la droite.
			sf::Vector2f pos = getPosition();
			sf::Vector2f halfSize = getDimension() * 0.5f;
			GameScene* game = getGameScene();
			// Limites horizontales.
			if (pos.x + halfSize.x + 1 < game->GAME_LEFT)
			{
				deactivate();
			}
			else if (pos.x - halfSize.x - 1 >= game->GAME_LEFT + game->GAME_WIDTH)
			{
				deactivate();
			}
		}

		Movable::update(deltaT);

		// Fait tirer l'ennemi si ça fait assez longtemps qu'il n'a pas tiré.
		fireTimer += sf::seconds(deltaT);
		if (fireTimer.asMilliseconds() >= fireRateMS)
		{
			fireTimer = sf::microseconds(0);
			if (!isDisabled)
			{
				fire();
			}
		}
	}
}

/// <summary>
/// Affiche l'ennemi sur la fenêtre.
/// </summary>
/// <param name="window">La fenêtre sur laquelle afficher l'ennemi.</param>
void Enemy::draw(sf::RenderWindow& window)
{
	if (isActivated())
	{
		RessourceManager::getInstance()->getSprite(getSpriteKey())->setColor(color);
		Movable::draw(window);
	}
}

/// <summary>
/// Réinitialise l'ennemi à un état de départ.
/// </summary>
void Enemy::reset()
{
	resetLife(defaultLife);
	setDirection(LEFT);
	setSpeed(GameScene::SCROLLING_SPEED);
	state = Spawning;
	fireTimer = sf::microseconds(0);

	// Détermine une couleur de l'ennemi au hasard.
	int colorIndex = rand() % 3;
	color = getGameScene()->getGameColor(colorIndex);
}

/// <summary>
/// Fait bouger l'ennemi au rythme du défilement de l'écran.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de update.</param>
void Enemy::scroll(const float deltaT)
{
	setPosition(getPosition() + (sf::Vector2f(-GameScene::SCROLLING_SPEED, 0) * deltaT));
}