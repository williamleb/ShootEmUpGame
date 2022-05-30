#include "Turret.h"
#include "GameScene.h"
#include"Player.h"


using namespace TP3;

/// <summary>
/// Crée une nouvele <see cref="Turret"/>.
/// </summary>
Turret::Turret()
	:Enemy(GameObject::TURRET, FIRE_RATE, DEFAULT_LIFE, ENEMI_DEFAULT_SPEED, POINTS_GIVEN, COLLISION_DAMAGE)
{

}

/// <summary>
/// Détruit une <see cref="Turret"/>.
/// </summary>
Turret::~Turret()
{
}

/// <summary>
/// Fait tirer l'ennemi.
/// </summary>
void Turret::fire()
{
	if (abs(angleCible-angle)<10)
	{
		GameScene* game = getGameScene();
		
		game->activateEnemyProjectile(GameObject::PROJECTILE_TURRET, this, angleCible/180 * M_PI, getPosition() + sf::Vector2f(0, 5));
	}
}
/// <summary>
/// Initialise la turret.
/// Doit être appelé une fois avant d'utiliser l'objet.
/// </summary>
/// <param name="spriteKey">Le sprite utilisé.</param>
void Turret::init(const RessourceManager::key spriteKey)
{
	
	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	sprite->setOrigin(TURRET_WIDTH / 2, TURRET_HEIGHT / 2);
	setDimension(TURRET_WIDTH, TURRET_HEIGHT);
	setDirection(Movable::LEFT);
	setSpeed(GameScene::SCROLLING_SPEED);
}

/// <summary>
/// Troune dans la direction du joueur.
/// </summary>
/// <param name="spriteKey">Le sprite de la tourette.</param>
void Turret::findPlayer(const RessourceManager::key spriteKey)
{
	Player *player = getPlayer();
	
	sf::Sprite* sprite = RessourceManager::getInstance()->operator[](spriteKey);
	sprite->setPosition(getPosition());
	//Si le joueur est a gauche de la turret...
	if (player->getPosition().x<getPosition().x)
	{
		// on ajoute 180 à l'angle cible
		angleCible = 180* atan(((player->getPosition().y - getPosition().y)) / (player->getPosition().x - getPosition().x))/M_PI +180;
	}
	//Si le joueur est à droite de la turret..
	else if (player->getPosition().x>getPosition().x)
	{
		angleCible = 180 * atan(((player->getPosition().y - getPosition().y)) / (player->getPosition().x - getPosition().x)) / M_PI;
	}
	if (angleCible<0)
	{
		angleCible += 360;
	}
	// si la différence entre l'angle de la tourelle et celle du joueur est supérieur a 10 degrée..
	if (abs(angle - angleCible) > 10)
	{
		if (angleCible<angle)
		{
			//rotation
			angle -= 2;
		}
		else
		{
			angle += 2;
		}

	}
	
}

/// <summary>
/// Update l'ennemi selon le temps écoulé.
/// </summary>
/// <param name="deltaT">Le nombre de secondes depuis le dernier appel de la méthode.</param>
void Turret::update(const float deltaT)
{
	findPlayer(getSpriteKey());
	Enemy::update(deltaT);
}

/// <summary>
/// Affiche l'ennemi sur la fenêtre.
/// </summary>
/// <param name="window">La fenêtre sur laquelle afficher l'ennemi.</param>
void Turret::draw(sf::RenderWindow& window)
{
	if (isActivated())
	{
		RessourceManager::getInstance()->getSprite(getSpriteKey())->setRotation(angle);
		Enemy::draw(window);
	}
}
