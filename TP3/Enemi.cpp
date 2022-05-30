#include "Enemi.h"
#include "GameScene.h"
#include "Player.h"
using namespace TP3;

Enemi::Enemi()
	:Enemy(GameObject::ENEMI,FIRE_RATE,DEFAULT_LIFE,ENEMI_DEFAULT_SPEED,POINTS_GIVEN,COLLISION_DAMAGE)
{
	
}

Enemi::~Enemi()
{
}

void Enemi::fire()
{
	GameScene* game = getGameScene();
	//Fait tirer l'enemi s'il est au même niveau que le joueur et qu'il est à sa droite.
	if (abs(joueur->getPosition().y - getPosition().y)<5 && joueur->getPosition().x<getPosition().x)
	{
		if (shootTimerInMs >= NBR_MS_BEFORE_SHOOT)
		{

			game->activateMovable(GameObject::LAZER, getPosition(), Movable::LEFT);
			shootTimerInMs = 0;
		}
	}
	
}

void Enemi::init(const RessourceManager::key spriteKey, Player *player)
{
	setDimension(WIDTH, HEIGHT);
	shootTimerInMs = 0;
	joueur = player;
	setSpeed(ENEMI_DEFAULT_SPEED);
	setSpriteKey(spriteKey);
	sf::Sprite* sprite = RessourceManager::getInstance()->getSprite(spriteKey);
	// TODO: Setdimensions
}



 void Enemi::update(const float deltaT)
{
	 setState(Enemy::State::Moving);
	 if (getPosition().y<0)
	 {
		 setPosition(600, 700);
	 }
	 deplacement.y = -1;
	 Movable::setDirection(deplacement);
	 Movable::update(deltaT);
	 shootTimerInMs++;
}

 void Enemi::draw(sf::RenderWindow & window)
 {
	 Movable::draw(window);
 }

 void Enemi::activate(const sf::Vector2f& position)
 {
	 setPosition(position);
	 Activatable::activate();
 }

 void TP3::Enemi::getType()
 {
 }

 
